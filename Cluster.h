//
// Created by zwpdbh on 15/05/2017.
//

#ifndef PLANEFINDER_PCA_H
#define PLANEFINDER_PCA_H

#include "SimplePly.h"
#include <Eigen/Eigenvalues>
#include <unordered_map>

class Cluster {

public:
    /**
     * constructors
     */
    Cluster() {};
    Cluster(std::vector<PlyPoint *>);

    std::vector<PlyPoint *> points;

    /**
     * my covariance matrix, the most variation component, centroid.
     */
    Eigen::Matrix3d cov;
    Eigen::Vector3d firstPC;
    Eigen::Vector3d secondPC;
    Eigen::Vector3d centroid;

    /**
     * associated eigenvalues and eigenvectors
     */
    Eigen::EigenSolver<Eigen::Matrix3d>::EigenvalueType  eigenvalues;
    Eigen::EigenSolver<Eigen::Matrix3d>::EigenvectorsType eigenvectors;

    /**
     * agglomerative clustering
     */
    static void agglomerativeClustering(SimplePly &ply);
private:
    /**
     * helper functions
     */
    double computeMean(std::vector<double> *d);
    double computeCovariance(std::vector<double> *d1, std::vector<double> *d2);
    void centerDataAtZero(std::vector<double> *d);
//    static double minDistanceAmongAllClusters(std::unordered_map<long, Cluster *> &clusters);
};


#endif //PLANEFINDER_PCA_H
