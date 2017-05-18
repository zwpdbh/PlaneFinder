//
// Created by zwpdbh on 11/05/2017.
//

#ifndef PLANEFINDER_PLANE_H
#define PLANEFINDER_PLANE_H

#include "SimplePly.h"
#include <unordered_map>

class Plane {
public:
    // constructors
    Plane(){}
    Plane(Eigen::Vector3d p1, Eigen::Vector3d p2, Eigen::Vector3d p3);

    // use this plane to fit the given data points
    std::vector<long> fitPlane(std::unordered_map<long, PlyPoint *> &dataSet, double threshold);

    // get the location of a point after projecting it onto this plane
    Eigen::Vector3d projectPointOnThisPlane(Eigen::Vector3d p);

    // compute the distance from point to plane
    double distanceFromPointToThisPlane(Eigen::Vector3d p);

    // my inner data structures
    std::vector<long> inliers;


    Eigen::Vector3d normalVector;

private:
    // my inner data structures
    Eigen::Vector3d p1;
    Eigen::Vector3d p2;
    Eigen::Vector3d p3;

    Eigen::Vector3d u;
    Eigen::Vector3d v;


//    PlyPoint *p1;
//    PlyPoint *p2;
//    PlyPoint *p3;
};


#endif //PLANEFINDER_PLANE_H
