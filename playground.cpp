//
// Created by zwpdbh on 06/05/2017.
//

#include "Cluster.h"
#include <iostream>
#include <map>
#include <unordered_map>

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


//    string inputFile = "/Users/zw/code/C++_Projects/PlaneFinder/data/adzePoints.ply";
//
//    // Storage for the point cloud.
//    SimplePly ply;
//
//    // Read in the data from a PLY file
//    std::cout << "Reading PLY data from " << inputFile << std::endl;
//    if (!ply.read(inputFile)) {
//        std::cout << "Could not read PLY data from file " << inputFile << std::endl;
//        return -1;
//    }
//    std::cout << "Read " << ply.size() << " points" << std::endl;


//    vector<PlyPoint *> testData;
//    for (unsigned long i = 0; i < 100; i++) {
//        testData.push_back(&ply[i]);
//    }
//    Cluster pca(testData);
//    cout << pca.eigenvalues << endl;
//    cout << pca.eigenvectors << endl;




//    Eigen::Matrix2d cov;
//    cov << 0.616555556, 0.615444444,
//            0.615444444, 0.716555556;
//
//    Eigen::EigenSolver<Eigen::Matrix2d> solver(cov);
//
//    cout << solver.eigenvalues().real() << endl;
//    cout << solver.eigenvalues().real()(0) << endl;
//    cout << solver.eigenvectors().real() << endl;
//    cout << solver.eigenvectors().real().col(0) << endl;


//    Eigen::Matrix3d test;
//    test << 3, 0, 1,
//            -4, 1, 2,
//            -6, 0, -2;
//
//    Eigen::EigenSolver<Eigen::Matrix3d> solver(test);
//
//    cout << solver.eigenvalues().real() << endl;
//    cout << solver.eigenvectors().real() << endl;
//    cout << solver.eigenvectors().real().col(0) << endl;




//    vector<PlyPoint *> patch;
//    unsigned long size = ply.size() / 10000;
//    cout << size << endl;
//
//    unordered_map<long, Cluster *> clusters;
//    long c = 0;
//    for (unsigned long i = 0; i < ply.size(); i++) {
//        if (patch.size() == size) {
//            Cluster cluster(patch);
//            clusters[c] = &cluster;
//            c += 1;
//            patch.clear();
//        }
//        patch.push_back(&ply[i]);
//    }
//
//    cout << clusters.size() << endl;
//
//    double threshold = 0.01;

    Eigen::Vector2d u(0, 1);
    Eigen::Vector2d v(1, 0);
    cout << acos(u.dot(v)) << endl;

    cout << pow(2, 10) << endl;
    return 0;
}