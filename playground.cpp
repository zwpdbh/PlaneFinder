//
// Created by zwpdbh on 06/05/2017.
//

#include "Plane.h"
#include "Cluster.h"
#include <iostream>
#include <map>
#include <unordered_map>


using namespace std;


int main(int argc, char *argv[]) {

//    string inputFile = "/Users/zw/code/C++_Projects/PlaneFinder/data/adzePoints.ply";
//    string outputFile = "/Users/zw/code/C++_Projects/PlaneFinder/data/output_adzePoints.ply";
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



    Eigen::Vector3d p1(1, 0, 0);
    Eigen::Vector3d p2(0, 0, 0);
    Eigen::Vector3d p3(0, 1, 0);

    Plane plane(p1, p2, p3);
    cout << "the normal vector of plane is: " << endl;
    cout << plane.normalVector << endl;

    Eigen::Vector3d p0(4, 5, -6);
    cout << "the distance from point (4, 5, -6) to plane is: " << plane.distanceFromPointToThisPlane(p0) << endl;
    cout << "after projecting the point on the plane, the point is: " << endl;
    cout << plane.projectPointOnThisPlane(p0) << endl;


    Eigen::Vector3d p5(4, 5, 6);
    cout << "the distance from point (4, 5, 6) to plane is: " << plane.distanceFromPointToThisPlane(p5) << endl;
    cout << "after projecting the point on the plane, the point is: " << endl;
    cout << plane.projectPointOnThisPlane(p5) << endl;
    return 0;
}