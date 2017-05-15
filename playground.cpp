//
// Created by zwpdbh on 06/05/2017.
//

#include "PCA.h"
#include <iostream>
#include <Eigen/Dense>
#include <map>

using namespace std;


double computeMean(std::vector<double> *d) {
    double total = 0;
    for (const double each: *d) {
        total += each;
    }
    return total / d->size();
}

void centerDataAtZero(std::vector<double> *d) {
    double mean = computeMean(d);
    for (unsigned long i = 0; i < d->size(); i++) {
        d->at(i) = d->at(i) - mean;
    }
}


int main(int argc, char *argv[]) {


    string inputFile = "/Users/zw/code/C++_Projects/PlaneFinder/data/adzePoints.ply";

    // Storage for the point cloud.
    SimplePly ply;

    // Read in the data from a PLY file
    std::cout << "Reading PLY data from " << inputFile << std::endl;
    if (!ply.read(inputFile)) {
        std::cout << "Could not read PLY data from file " << inputFile << std::endl;
        return -1;
    }
    std::cout << "Read " << ply.size() << " points" << std::endl;




//
//    Eigen::Vector3d point = ply[1].location;
//    cout << point << endl;
//    cout << point[0] << endl;

//    vector<double> data;
//    data.push_back(0.1);
//    data.push_back(0.2);
//    data.push_back(0.3);
//
//    centerDataAtZero(&data);
//    cout << data.at(0) << " "  << data.at(1) << " "  << data.at(2) << endl;

//    Eigen::Matrix3d cov;
//    cov << 1, 2, 3,
//            4, 5, 6,
//            7, 8, 9;
//
//    cout << cov.eigenvalues() << endl;


    unsigned long counter = 0;
    vector<PlyPoint *> patch;
    for (unsigned long i = 0; i < ply.size(); i++) {
        if (patch.size() == 100) {
            PCA pca(patch);
            cout << endl;
            cout << pca.cov.eigenvalues() << endl;
            cout << endl;
            patch.clear();
        }
        patch.push_back(&ply[i]);
    }


    return 0;
}