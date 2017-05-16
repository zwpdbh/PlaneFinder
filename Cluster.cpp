//
// Created by zwpdbh on 15/05/2017.
//

#include "Cluster.h"
#include <iostream>
#include <unordered_map>

using namespace std;

Cluster::Cluster(SimplePly &ply, vector<long> &points) {
    this->points = points;

//    points.at(1)->location.
    vector<double> xDimension;
    vector<double> yDimension;
    vector<double> zDimension;

    for (unsigned long i = 0; i < this->points.size(); i++) {
        xDimension.push_back(ply[this->points[i]].location[0]);
        yDimension.push_back(ply[this->points[i]].location[1]);
        zDimension.push_back(ply[this->points[i]].location[2]);
    }


    vector<vector<double> *> data;
    data.push_back(&xDimension);
    data.push_back(&yDimension);
    data.push_back(&zDimension);

    // 1. construct the covariance matrix, 3 by 3
    for (unsigned long i = 0; i < data.size(); i++) {
        for (unsigned long j = 0; j < data.size(); j++) {
            this->cov(i, j) = computeCovariance(data.at(i), data.at(j));
        }
    }

    // 2. computer eigenvalues and eigenvectors
    Eigen::EigenSolver<Eigen::Matrix3d> solver(this->cov);
    this->eigenvalues = solver.eigenvalues();
    this->eigenvectors = solver.eigenvectors();


    // 3. get the two largest eigenvalues
    int first, second;
    if (this->eigenvalues.real()(0) > this->eigenvalues.real()(1)) {
        first = 0;
        second = 1;
    } else {
        first = 1;
        second = 0;
    }
    if (this->eigenvalues.real()(first) > this->eigenvalues.real()(2)) {
        if (this->eigenvalues.real()(2) > this->eigenvalues.real()(second)) {
            second = 2;
        }
    } else {
        second = first;
        first = 2;
    }

    // initialization
    this->firstPC = this->eigenvectors.real().col(first);
    this->secondPC = this->eigenvectors.real().col(second);
    this->centroid[0] = computeMean(&xDimension);
    this->centroid[1] = computeMean(&yDimension);
    this->centroid[2] = computeMean(&zDimension);

}

double Cluster::computeMean(std::vector<double> *d) {
    double total = 0;
    for (const double each: *d) {
        total += each;
    }
    return total / d->size();
}

double Cluster::computeCovariance(std::vector<double> *d1, std::vector<double> *d2) {
    if (d1->size() != d2->size()) {
        cout << "The dimensions between these two data must be same!" << endl;
        return 0;
    }

    unsigned long size = d1->size();

    double m1 = computeMean(d1);
    double m2 = computeMean(d2);

    double total = 0;

    for (unsigned long i = 0; i < size; ++i) {
        total += ((d1->at(i) - m1) * (d2->at(i) - m2));
    }

    return total / size;
}

void Cluster::centerDataAtZero(std::vector<double> *d) {
    double mean = computeMean(d);
    for (unsigned long i = 0; i < d->size(); i++) {
        d->at(i) = d->at(i) - mean;
    }
}


/**
 * The distance between my two clusters is a measurement of how similar the two cluster are.
 * This is computed by comparing the similariy of two pairs of eigenvectors. These two pairs
 * eigenvectors are those contains the most variations (pick the two most variant dimention).
 */
double dissimilarityBetween(Cluster *c1, Cluster *c2) {
    // compute the difference between their fist and second PCs
    double distance = pow(acos(c1->firstPC.dot(c1->firstPC)), 2) + pow(acos(c1->secondPC.dot(c2->secondPC)), 2);
    return distance;
}

struct MinPair {
    unsigned long i;
    unsigned long j;
    double distance;
};

/**
 * compute the min distance among all the pairs of clusters
 * @param clusters a pointer to unordered map
 */
static MinPair minDistanceAmongAllClusters(std::unordered_map<long, Cluster *> &clusters) {
    MinPair minPair = {};
    double minDistance = 100000000;
    // compute all pairs of clusters' distance
    unsigned long size = clusters.size();
    for (unsigned long i = 0; i < size; i++) {
        Cluster *clusterI = clusters[i];
        for (unsigned long j = i + 1; j < size; j++) {
            Cluster *clusterJ = clusters[j];
            double currentDistance = dissimilarityBetween(clusterI, clusterJ);
            if (minDistance < currentDistance) {
                minDistance = currentDistance;
                minPair.distance = minDistance;
                minPair.i = i;
                minPair.j = j;
            }
        }
    }
    return minPair;
}



void Cluster::agglomerativeClustering(SimplePly &ply) {
    unordered_map<long, Cluster *> clusters;
    vector<long> groupOfPoints;
    long c = 0;

    for (long i = 0; i < ply.size(); i++) {
        if (groupOfPoints.size() > 100) {
            Cluster cluster(ply, groupOfPoints);
            clusters[c] = &cluster;
            c += 1;
            groupOfPoints.clear();
        }
        groupOfPoints.push_back(i);
    }

    cout << "The initial size of clusters is: " << clusters.size() << endl;

    double threshold = 0.02;
    do {
        MinPair minPair = minDistanceAmongAllClusters(clusters);
        if (minPair.distance > threshold) {
            break;
        } else {
            Cluster *clusterI = clusters[minPair.i];
            Cluster *clusterJ = clusters[minPair.j];

            // merge these two cluster
            vector<long> tmp;
            for (long each :clusterI->points) {
                tmp.push_back(each);
            }
            for (long each :clusterJ->points) {
                tmp.push_back(each);
            }

            // add the merged new cluster
            Cluster mergedCluster(ply, tmp);
            clusters[minPair.i] = &mergedCluster;

            // remove the clusters for clusterI and clusterJ
            clusters.erase(minPair.j);
        }
    } while (true);

    cout << "After agglomerative clustering, the size of clusters reduced to : "
         << clusters.size() << endl;


    // colour the points based on cluster

    vector<Eigen::Vector3i> colours;
    for (int i = 0; i < 8; i++) {
        colours.push_back(Eigen::Vector3i(204, 51, 255));
        colours.push_back(Eigen::Vector3i(255, 102, 102));
        colours.push_back(Eigen::Vector3i(230, 0, 172));
        colours.push_back(Eigen::Vector3i(255, 255, 0));
        colours.push_back(Eigen::Vector3i(0, 204, 0));
        colours.push_back(Eigen::Vector3i(198, 140, 83));
        colours.push_back(Eigen::Vector3i(153, 204, 255));
    }

    int count = 0;
    for (auto it = clusters.begin(); it != clusters.end(); it++) {
        cout << "The " << count + 1 << "th cluster's size = " << it->second->points.size()
             << "percentage: " << (double) it->second->points.size() / ply.size() << endl;
        Eigen::Vector3i colour = colours[count];
        for (long index: it->second->points) {
            ply[index].colour = colour;
        }
        count += 1;
    }
}



