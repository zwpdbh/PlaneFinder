//
// Created by zwpdbh on 11/05/2017.
//

#ifndef PLANEFINDER_PLANE_H
#define PLANEFINDER_PLANE_H

#include "SimplePly.h"
#include <unordered_map>

class Plane {
public:
    Plane(){}
    Plane(PlyPoint *p1, PlyPoint *p2, PlyPoint *p3);
    std::vector<long> fitPlane(std::unordered_map<long, PlyPoint *> &dataSet, double threshold);
    std::vector<long> inliers;
    Eigen::Vector3d normalVector;
    Eigen::Vector3d projectPointOnThisPlane(PlyPoint &p);
private:
    PlyPoint *p1;
    PlyPoint *p2;
    PlyPoint *p3;
};


#endif //PLANEFINDER_PLANE_H
