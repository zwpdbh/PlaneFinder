#include "SimplePly.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {

    // Check the commandline arguments.
//  if (argc != 6) {
//    std::cout << "Usage: planeFinder <input file> <output file> <number of planes> <point-plane threshold> <number of RANSAC trials>" << std::endl;
//    return -1;
//  }
//  int nPlanes = atoi(argv[3]);
//  double threshold = atof(argv[4]);
//  int nTrials = atoi(argv[5]);

    int nPlanes = 3;
    double threshold = 0.01;
    int nTrials = 1000;

    string inputFile = "/Users/zw/code/C++_Projects/PlaneFinder/data/adzePoints.ply";
    string outputFile = "/Users/zw/code/C++_Projects/PlaneFinder/data/output_adzePoints.ply";


    std::cout << "Searching for " << nPlanes << " planes" << std::endl;
    std::cout << "Using a point-plane threshold of " << threshold << " units" << std::endl;
    std::cout << "Applying RANSAC with " << nTrials << " trials" << std::endl;

    // Storage for the point cloud.
    SimplePly ply;

    // Read in the data from a PLY file
    std::cout << "Reading PLY data from " << inputFile << std::endl;
    if (!ply.read(inputFile)) {
        std::cout << "Could not read PLY data from file " << inputFile << std::endl;
        return -1;
    }
    std::cout << "Read " << ply.size() << " points" << std::endl;

    // Recolour points - here we are just doing colour based on index
    std::cout << "Recolouring points" << std::endl;
    std::vector<Eigen::Vector3i> colours;
    colours.push_back(Eigen::Vector3i(255, 0, 0));
    colours.push_back(Eigen::Vector3i(0, 255, 0));
    colours.push_back(Eigen::Vector3i(0, 0, 255));
    // Can add more colours as needed

    // each planeSize holds the number of points = total / num of plane
    size_t planeSize = ply.size() / nPlanes;

    for (size_t index = 0; index < ply.size(); ++index) {
        size_t indexInPlane = index / planeSize;
        size_t colourIx = indexInPlane % colours.size(); // May need to recycle colours
        ply[index].colour = colours[colourIx];
    }

    // Write the resulting (re-coloured) point cloud to a PLY file.
    std::cout << "Writing PLY data to " << outputFile << std::endl;
    if (!ply.write(outputFile)) {
        std::cout << "Could not write PLY data to file " << outputFile << std::endl;
        return -2;
    }

    return 0;
}
