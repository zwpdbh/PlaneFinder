//
// Created by zwpdbh on 06/05/2017.
//

#include "Patch.h"
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


//    vector<PlyPoint *> testData;
//    for (unsigned long i = 0; i < 100; i++) {
//        testData.push_back(&ply[i]);
//    }
//    Patch pca(testData);
//    cout << pca.eigenvalues << endl;
//    cout << pca.eigenvectors << endl;




//    Eigen::Matrix2d cov;
//    cov << 6, -1,
//            2, 3;
//
//    Eigen::EigenSolver<Eigen::Matrix2d> solver(cov);
//
//    cout << solver.eigenvalues().real() << endl;
//    cout << solver.eigenvectors().real() << endl;
//    cout << solver.eigenvectors().real().col(0) << endl;



    vector<PlyPoint *> patch;
    unsigned long size = ply.size() / 10000;
    cout << size << endl;

    for (unsigned long i = 0; i < ply.size(); i++) {
        if (patch.size() == size) {
            Patch pca(patch);
            cout << endl;
            cout << pca.eigenvectors.real() << endl;
            cout << endl;
            patch.clear();
        }
        patch.push_back(&ply[i]);
    }

    return 0;
}