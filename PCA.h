//
// Created by zwpdbh on 15/05/2017.
//

#ifndef PLANEFINDER_PCA_H
#define PLANEFINDER_PCA_H

#include "SimplePly.h"

class PCA {
public:
    PCA() {};
    PCA(std::vector<PlyPoint *>);
    Eigen::Matrix3d cov;

private:
    double computeMean(std::vector<double> *d);
    double computeCovariance(std::vector<double> *d1, std::vector<double> *d2);
    void centerDataAtZero(std::vector<double> *d);
};


#endif //PLANEFINDER_PCA_H
