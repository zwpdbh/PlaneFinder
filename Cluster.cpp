//
// Created by zwpdbh on 15/05/2017.
//

#include "Cluster.h"
#include <iostream>

using namespace std;

Cluster::Cluster(std::vector<PlyPoint *> points) {
//    points.at(1)->location.
    vector<double> xDimension;
    vector<double> yDimension;
    vector<double> zDimension;

    for (unsigned long i = 0; i < points.size(); i++) {
        xDimension.push_back(points.at(i)->location[0]);
        yDimension.push_back(points.at(i)->location[1]);
        zDimension.push_back(points.at(i)->location[2]);
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
double Cluster::distanceBetween(Cluster *c1, Cluster *c2) {
    // compute the difference between their fist and second PCs
    double distance = pow(acos(c1->firstPC.dot(c1->firstPC)), 2) + pow(acos(c1->secondPC.dot(c2->secondPC)), 2);

    return distance;
}

void Cluster::agglomerativeClustering(SimplePly *) {


}
