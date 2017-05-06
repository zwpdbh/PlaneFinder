//
// Created by zwpdbh on 06/05/2017.
//

#include "Plane.h"
#include <Eigen/Dense>
using namespace std;

Plane::Plane(PlyPoint p1, PlyPoint p2, PlyPoint p3) {
    this->v0 = p2.location;
    this->u = p1.location - p2.location;
    this->v = p3.location - p2.location;
    this->norm = this->u.cross(this->v);
    this->normalized = this->norm / sqrt(this->norm.dot(this->norm));
    //The point on plane meet the equation norm.dot(P-v2) = 0, P(x, y z)
}

double Plane::distanceToThisPlane(PlyPoint p0) {
    return fabs(this->normalized.dot(p0.location - this->v0));
}

bool Plane::isInlier(PlyPoint p, double threshold) {
    return distanceToThisPlane(p) < threshold;
}

std::vector<int> Plane::getInliersIndex(std::vector<PlyPoint> data, double threshold){
    vector<int> inliers;

    for (int i = 0; i < data.size(); ++i) {
        if (this->isInlier(data[0], threshold)) {
            inliers.push_back(i);
        }
    }
    return inliers;
}

