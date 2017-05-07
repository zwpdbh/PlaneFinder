//
// Created by zwpdbh on 06/05/2017.
//

#include "Plane.h"
#include <Eigen/Dense>
using namespace std;


Eigen::Vector3i generateRandomColor() {
    int defaultColor = 107;

    Eigen::Vector3i colourDefault(defaultColor, defaultColor, defaultColor);

    int rColor;
    int gColor;
    int bColor;

    // 107 will be the default colour for point
    do {
        rColor = rand() % 230 + 10;
        gColor = rand() % 230 + 10;
        bColor = rand() % 230 + 10;
    } while (rColor == defaultColor && gColor == defaultColor && bColor== defaultColor);

    return Eigen::Vector3i(rColor, gColor, bColor);
}

Plane::Plane(unsigned long p1, unsigned long p2, unsigned long p3, SimplePly ply) {
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    this->v0 =ply[this->p1].location;
    this->u = ply[this->p1].location - ply[this->p3].location;
    this->v = ply[this->p3].location - ply[this->p2].location;
    this->norm = this->u.cross(this->v);
    this->normalized = this->norm / sqrt(this->norm.dot(this->norm));
    //The point on plane meet the equation norm.dot(P-v2) = 0, P(x, y z)
    this->color = generateRandomColor();
}

double Plane::distanceToThisPlane(PlyPoint p0) {
    return fabs(this->normalized.dot(p0.location - this->v0));
}

bool Plane::isInlier(SimplePly ply, unsigned long p, double threshold) {
    return distanceToThisPlane(ply[p]) < threshold;
}

