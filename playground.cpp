//
// Created by zwpdbh on 06/05/2017.
//

#include "SimplePly.h"
#include <iostream>
#include <Eigen/Dense>
#include <map>
using namespace std;

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



    return 0;
}