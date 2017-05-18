//
// Created by zwpdbh on 11/05/2017.
//


#include "Plane.h"
#include <Eigen/Dense>


/**
 * Plane use 3 PlyPoints to construct .
 */
Plane::Plane(Eigen::Vector3d p1, Eigen::Vector3d p2, Eigen::Vector3d p3) {
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    this->u = this->p1 - this->p2;
    this->v = this->p3 - this->p2;
    Eigen::Vector3d norm = u.cross(v);
    this->normalVector = norm / sqrt(norm.dot(norm));
}


/**
 * use this plane to fit a cloud of PlyPoints
 * @param dataSet it is an unordered map, used for storing the clould of PlyPoints
 * @param threshold it is the distance from a point in dataSet to this plane
 * @return std::vector<long> return the fitted PlyPoints' indexes as a vector<long>
 */
std::vector<long> Plane::fitPlane(std::unordered_map<long, PlyPoint *> &dataSet, double threshold) {
    for (auto const &each: dataSet) {
        double d = fabs(this->normalVector.dot(each.second->location - this->p2));
        if (d < threshold) {
            this->inliers.push_back(each.first);
        }
    }

    return this->inliers;
}


/**
 * Project an arbitary point p on to this plane
 */
Eigen::Vector3d Plane::projectPointOnThisPlane(Eigen::Vector3d p) {
    double d = fabs(this->normalVector.dot(p - this->p2));
    Eigen::Vector3d projectedPoint = p - d * this->normalVector;
    return projectedPoint;
}
