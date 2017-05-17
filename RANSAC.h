//
// Created by zwpdbh on 16/05/2017.
//

#ifndef PLANEFINDER_RANSAC_H
#define PLANEFINDER_RANSAC_H


#include "Plane.h"

class RANSAC {
public:
    /**
     * data members
     */
    int nPlanes;
    double threshold;
    double expectedOutlierRatio;
    double expectedSuccessfulRate;

    /**
     * my constructor
     */
    RANSAC(int nPlanes, double threshold, double expectedOutlierRatio, double expectedSuccessfulRate);

    /**
     * call this method to use RANSAC to fit planes in the Simply with initialized parameters
     */
    void fitPlyPoints(SimplePly &ply);
};


#endif //PLANEFINDER_RANSAC_H
