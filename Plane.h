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
    Plane(PlyPoint *p1, PlyPoint *p2, PlyPoint *p3);

    // method to use this plane to fit the given data points
    std::vector<long> fitPlane(std::unordered_map<long, PlyPoint *> &dataSet, double threshold);

    // method to get the location of projecting a point on this plane
    Eigen::Vector3d projectPointOnThisPlane(PlyPoint &p);

    // my inner data structures
    std::vector<long> inliers;
    Eigen::Vector3d normalVector;
    Eigen::Vector3d pointP;

    /**
     * Project an arbitary point p on to this plane
     */
    Eigen::Vector3d pointProjectedOnThisPlane;

private:
    // my inner data structures
    PlyPoint *p1;
    PlyPoint *p2;
    PlyPoint *p3;
};


#endif //PLANEFINDER_PLANE_H
