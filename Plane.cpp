//
// Created by zwpdbh on 11/05/2017.
//


#include "Plane.h"
#include <Eigen/Dense>

Plane::Plane(PlyPoint *p1, PlyPoint *p2, PlyPoint *p3) {
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
}

std::vector<long> Plane::fitPlane(std::unordered_map<long, PlyPoint *> &dataSet, double threshold) {

    Eigen::Vector3d p0 = this->p1->location;
    Eigen::Vector3d p1 = this->p2->location;
    Eigen::Vector3d p2 = this->p3->location;

    Eigen::Vector3d u = p0 - p1;
    Eigen::Vector3d v = p2 - p1;
    Eigen::Vector3d norm = u.cross(v);
    Eigen::Vector3d normalized = norm / sqrt(norm.dot(norm));
    this->normalVector = normalized;

    for (auto const &each: dataSet) {
        double d = fabs(normalized.dot(each.second->location - p1));
        if (d < threshold) {
            this->inliers.push_back(each.first);
        }
    }

    return this->inliers;
}

Eigen::Vector3d Plane::projectPointOnThisPlane(PlyPoint &p) {

    return Eigen::Vector3d();
}
