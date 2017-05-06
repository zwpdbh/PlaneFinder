//
// Created by zwpdbh on 06/05/2017.
//

#ifndef PLANEFINDER_PLANE_H
#define PLANEFINDER_PLANE_H


#include "SimplePly.h"

class Plane {

public:
    Plane(PlyPoint p1, PlyPoint p2, PlyPoint p3);
    bool isInlier(PlyPoint p, double threshold);
    std::vector<int> getInliersIndex(std::vector<PlyPoint> data, double threshold);

private:
    Eigen::Vector3d u;
    Eigen::Vector3d v;
    Eigen::Vector3d norm;
    Eigen::Vector3d normalized;
    Eigen::Vector3d v0;
    double distanceToThisPlane(PlyPoint p0);
};


#endif //PLANEFINDER_PLANE_H
