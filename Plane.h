//
// Created by zwpdbh on 06/05/2017.
//

#ifndef PLANEFINDER_PLANE_H
#define PLANEFINDER_PLANE_H


#include "SimplePly.h"

class Plane {

public:
    Plane() {};
    Plane(unsigned long p1, unsigned long p2, unsigned long p3, SimplePly ply);
    bool isInlier(SimplePly ply, unsigned long p, double threshold);
    std::vector<unsigned long> inliers;
    Eigen::Vector3i color;
private:
    unsigned long p1;
    unsigned long p2;
    unsigned long p3;
    Eigen::Vector3d u;
    Eigen::Vector3d v;
    Eigen::Vector3d norm;
    Eigen::Vector3d normalized;
    Eigen::Vector3d v0;

    double distanceToThisPlane(PlyPoint p0);
};


#endif //PLANEFINDER_PLANE_H
