//
// Created by zwpdbh on 15/05/2017.
//

#include "Cluster.h"
#include <iostream>

using namespace std;


const double Cluster::neighbourConstraint = 0.02;
const double Cluster::eigenvectorDifferences = 2;

/**
 * My Cluster is a vector of long which is the index of data points in SimplyPly
 */
Cluster::Cluster(SimplePly &ply, vector<long> &points) {
    this->points = points;

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
//    this->centroid[0] = computeMean(&xDimension);
//    this->centroid[1] = computeMean(&yDimension);
//    this->centroid[2] = computeMean(&zDimension);

}

/**
 * compute the mean of a vectors of double
 * @param d the vectors of double
 * @return the mean
 */
double Cluster::computeMean(std::vector<double> *d) {
    double total = 0;
    for (const double each: *d) {
        total += each;
    }
    return total / d->size();
}

/**
 * return the covariance between two vectors
 * @param d1 vector1
 * @param d2 vector2
 */
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

/**
 * put the data's center to zero
 * @param d a vector of double, it's center will be put at zero
 */
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
double dissimilarityBetween(Cluster &c1, Cluster &c2) {
    // compute the difference between their fist and second PCs

    double distance = pow(acos(c1.firstPC.dot(c2.firstPC)), 2) + pow(acos(c1.secondPC.dot(c2.secondPC)), 2);
    return distance;
}

/**
 * return the distance between two points
 */
double computeDistanceAmongTwoPoints(PlyPoint &p1, PlyPoint &p2) {
    Eigen::Vector3d d = p1.location - p2.location;
    return sqrt(d.dot(d));
}

/**
 * I want to add a constraint on when merging the two clusters
 * They better be close to each other, this function will compute the closest distance between two Clusters
 * However it costs too much time.
 * @param c1 one cluster
 * @param c2 aonther cluster
 * @param ply the data set hold the points
 */
double closestDistanceBetweenTwoClusters(Cluster &c1, Cluster &c2, SimplePly &ply) {
    double distance = 1000000;

    for (int i = 0; i < c1.points.size(); i++) {
        for (int j = 0; j< c2.points.size(); j++) {
            double currentDistance = computeDistanceAmongTwoPoints(ply[c1.points[i]], ply[c2.points[j]]);
            if (currentDistance < distance) {
                distance = currentDistance;
            }
        }
    }
    return distance;
}

/**
 * structure make me to reture multiple values:
 * i, j represent the indexes of the picked two clusters
 * differences represent the differences among these two clusters
 */
struct MinPair {
    long i;
    long j;
    double differences;
};

/**
 * compute the min distance among all the pairs of clusters
 * @param clusters a pointer to unordered map
 */
static MinPair minDifferencesAmongClusters(std::unordered_map<long, Cluster> &clusters, SimplePly &ply) {
    MinPair minPair = {};
    double minDifferences = 100000000;
    // compute all pairs of clusters' differences
    unsigned long size = clusters.size();


    for (auto ci = clusters.begin(); ci != clusters.end(); ci++) {
        for (auto cj = clusters.begin(); cj != clusters.end(); cj++) {
            if (ci->first != cj->first) {
//                if (closestDistanceBetweenTwoClusters(ci->second, cj->second, ply) > Cluster::neighbourConstraint) {
//                    continue;
//                }
                double currentDifferences = dissimilarityBetween(ci->second, cj->second);
                if (currentDifferences < minDifferences) {
                    minDifferences = currentDifferences;
//                    cout << "min differences: " << minDifferences << " => (" << ci->first << ", " << cj->first << ")" << endl;
                    minPair.differences = minDifferences;
                    minPair.i = ci->first;
                    minPair.j = cj->first;
                }
            }
        }
    }

    return minPair;
}

/**
 * generate a cluster from the data set
 * @param dataSet the data set holds the real data: PlyPoints
 * @param clusterSize the size of cluster to initially generated
 */
vector<long> getNextCluster(unordered_map<long, PlyPoint *> &dataSet, int clusterSize) {
    vector<long> nextCluster;
    int c = 1;
    for (auto it = dataSet.begin(); it != dataSet.end(); it++) {
        if ( c > clusterSize) {
            break;
        }
        nextCluster.push_back(it->first);
        c++;
    }

    for (long i: nextCluster) {
        dataSet.erase(i);
    }
    return nextCluster;
}

/**
 * helper function to check the content of clusters
 */
void printOutClusters(unordered_map<long, Cluster> &clusters) {
    for (auto it = clusters.begin(); it != clusters.end(); it++) {
        cout << "cluster: " << it->first << " -> " << it->second.points.size() << endl;
    }
}

/**
 * merge a cluster with some cluster among an unordered_map of clusters:
 * if the unordered_map is empty, just add the cluster into it
 * if unordered_map is not empty, pick a most similar cluster with this and merge them.
 */
void mergeClusters(Cluster &currentCluster, unordered_map<long, Cluster> &clusters, SimplePly &ply) {
    if (clusters.size() == 0) {
        clusters[0] = currentCluster;
    } else {
        // compare with each cluster in the clusters, and pick a most similar one and merge them
        long key = 0;
        double minDissimilarity = 10;
        double threshold = 0.05;
        for (auto it = clusters.begin(); it != clusters.end(); it++) {
            double dissimilarity = dissimilarityBetween(it->second, currentCluster);

            if (dissimilarity < minDissimilarity) {
                cout << "current min dissimilarity is with cluster " << it->first << " = " << dissimilarity << endl;
                key = it->first;
                minDissimilarity  = dissimilarity;
            }
        }

        if (minDissimilarity < threshold) {
            // merge these two cluster
            cout << "dissimilarity is < threshold, merge into clusters.. " << endl;
            cout << "before merging, the cluster size is: " << clusters.size() << endl;
            vector<long> tmp;
            for (long each :clusters[key].points) {
                tmp.push_back(each);
            }
            for (long each :currentCluster.points) {
                tmp.push_back(each);
            }

            Cluster mergedOne(ply, tmp);
            clusters.erase(key);
            clusters[key] = mergedOne;
            cout << "after merging, the cluster size is: " << clusters.size() << endl;
            cout << "\n" << endl;
        } else {
            cout << "dissimilarity is > threshold, add into clusters.." << endl;
            clusters[clusters.size()] = currentCluster;
            cout << "after adding, the cluster size is: " << clusters.size() << endl;
            cout << "\n" << endl;
        }

    }
}

/**
 * In this process, it will keep generating a cluster from data: SimplePly, base on cluster size
 * It will merge this newly generated cluster with the unordered_map clusters.
 * After this process, unordered_map clusters will be filled with roughly clustered clusters..
 */
void preClustering(SimplePly &ply, int clusterSize, unordered_map<long, Cluster> &clusters) {
    cout << "each initial cluster size: " << clusterSize << endl;
    long totalSize = ply.size();

    unordered_map<long, PlyPoint *> dataSet;
    for (long i = 0; i < totalSize; i++) {
        dataSet[i] = &ply[i];
    }


    // keep get a new cluster for fit.
    while (true) {
        vector<long> points = getNextCluster(dataSet, clusterSize);
        if (points.size() < clusterSize / 2) {
            break;
        }

        Cluster currentCluster(ply, points);
        cout << "preparing merge cluster into clusters ....." << endl;
        mergeClusters(currentCluster, clusters, ply);
    }
}


/**
 *
 */
void Cluster::agglomerativeClustering(SimplePly &ply, int clusterSize) {
    unordered_map<long, Cluster> clusters;

    preClustering(ply, clusterSize, clusters);

    printOutClusters(clusters);

    do {
        MinPair minPair = minDifferencesAmongClusters(clusters, ply);
        if (minPair.differences > Cluster::eigenvectorDifferences) {
            break;
        }

        Cluster clusterI = clusters[minPair.i];
        Cluster clusterJ = clusters[minPair.j];

        // merge these two cluster
        vector<long> tmp;
        for (long each :clusterI.points) {
            tmp.push_back(each);
        }
        for (long each :clusterJ.points) {
            tmp.push_back(each);
        }


        // remove the clusters for clusterI and clusterJ
        clusters.erase(minPair.j);
        clusters.erase(minPair.i);
        // add the merged new cluster
        Cluster mergedCluster(ply, tmp);
        clusters[minPair.i] = mergedCluster;
        cout << "After merging clusters: (" << minPair.i << ", " << minPair.j
             << ") with min differences = " << minPair.differences
             << ", the current clusters' size is: " << clusters.size() << endl;

    } while (true);


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
        cout << "The " << count + 1 << "th cluster's size = " << it->second.points.size()
             << " percentage: " << (double) it->second.points.size() / ply.size() << endl;

        Eigen::Vector3i colour = colours[count];

        for (long index: it->second.points) {
            ply[index].colour = colour;
        }
        count += 1;
    }

}



