//
// Created by zwpdbh on 09/05/2017.
//
#include "SimplePly.h"

#ifndef PLANEFINDER_MEANSHIFT_H
#define PLANEFINDER_MEANSHIFT_H


class MeanShift {
public:
    MeanShift(double bandwidth);
    void fit(SimplePly data);
private:
    double bandwidth;
};


#endif //PLANEFINDER_MEANSHIFT_H
