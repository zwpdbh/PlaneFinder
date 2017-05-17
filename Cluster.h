//
// Created by zwpdbh on 15/05/2017.
//



#ifndef PLANEFINDER_PCA_H
#define PLANEFINDER_PCA_H


#include "Plane.h"
#include <Eigen/Eigenvalues>
#include <unordered_map>


/**
 * Each Cluster represent a group of points, represented by a vector<long> which holds
 * the point index in a Simply.
 */
class Cluster {
public:
    // threshold for differences between eigenvectors
    static const double eigenvectorDifferences;
    // threshold on the neighbour constraint
    static const double neighbourConstraint;

    // holds the groups of indexes which associated with PlyPoint in Simply
    std::vector<long> points;

    /**
     * my covariance matrix, the most variation component, centroid.
     */
    Eigen::Matrix3d cov;
    Eigen::Vector3d firstPC;
    Eigen::Vector3d secondPC;


    /**
     * associated eigenvalues and eigenvectors
     */
    Eigen::EigenSolver<Eigen::Matrix3d>::EigenvalueType  eigenvalues;
    Eigen::EigenSolver<Eigen::Matrix3d>::EigenvectorsType eigenvectors;


    Cluster() {};
    Cluster(SimplePly &ply, std::vector<long> &points);

    // agglomerative clustering
    static void agglomerativeClustering(SimplePly &ply, int clusterSize);

private:
    /**
     * helper functions
     */
    double computeMean(std::vector<double> *d);
    double computeCovariance(std::vector<double> *d1, std::vector<double> *d2);
    void centerDataAtZero(std::vector<double> *d);
//    static double minDifferencesAmongClusters(std::unordered_map<long, Cluster *> &clusters);
};


#endif //PLANEFINDER_PCA_H
