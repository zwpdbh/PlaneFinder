//
// Created by zwpdbh on 09/05/2017.
//

#include "MeanShift.h"

using namespace std;

MeanShift::MeanShift(double bandwidth) {
    this->bandwidth = bandwidth;
}

void MeanShift::fit(SimplePly data) {
    vector<PlyPoint> centroids;

    for (int i = 0; i < data.size(); i++) {
        centroids.push_back(data[i]);
    }

    while (true) {
        vector<PlyPoint> newCentroids;
        for (int i = 0; i < centroids.size(); i++) {
            vector<double> bandwidth;

            PlyPoint centroid = centroids[i];


        }
    }
}
