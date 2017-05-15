//
// Created by zwpdbh on 15/05/2017.
//

#include "PCA.h"
#include <iostream>

using namespace std;

PCA::PCA(std::vector<PlyPoint *> points) {
//    points.at(1)->location.
    vector<double> xDimension;
    vector<double> yDimension;
    vector<double> zDimension;

    for (unsigned long i = 0; i < points.size(); i++) {
        xDimension.push_back(points.at(i)->location[0]);
        yDimension.push_back(points.at(i)->location[1]);
        zDimension.push_back(points.at(i)->location[2]);
    }

    // 1. center the data at zero
    centerDataAtZero(&xDimension);
    centerDataAtZero(&yDimension);
    centerDataAtZero(&yDimension);

    vector<vector<double> *> data;
    data.push_back(&xDimension);
    data.push_back(&yDimension);
    data.push_back(&zDimension);

    // 2. construct the covariance matrix, 3 by 3
    for (unsigned long i = 0; i < data.size(); i++) {
        for (unsigned long j = 0; j < data.size(); j++) {
            this->cov(i, j) = computeCovariance(data.at(i), data.at(j));
        }
    }

}

double PCA::computeMean(std::vector<double> *d) {
    double total = 0;
    for (const double each: *d) {
        total += each;
    }
    return total / d->size();
}

double PCA::computeCovariance(std::vector<double> *d1, std::vector<double> *d2) {
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

void PCA::centerDataAtZero(std::vector<double> *d) {
    double mean = computeMean(d);
    for (unsigned long i = 0; i < d->size(); i++) {
        d->at(i) = d->at(i) - mean;
    }
}
