
#include <iostream>
#include "RANSAC.h"
#include "Cluster.h"

using namespace std;

int main(int argc, char *argv[]) {

    string inputFile = "/Users/zw/code/C++_Projects/PlaneFinder/data/adzePoints.ply";
    string outputFile = "/Users/zw/code/C++_Projects/PlaneFinder/data/output_adzePoints.ply";

    // Storage for the point cloud.
    SimplePly ply;

    // Read in the data from a PLY file
    std::cout << "Reading PLY data from " << inputFile << std::endl;
    if (!ply.read(inputFile)) {
        std::cout << "Could not read PLY data from file " << inputFile << std::endl;
        return -1;
    }


//
//    RANSAC ransac(10, 0.05, 0.95, 0.99);
//    ransac.fitPlyPoints(ply);

    Cluster::agglomerativeClustering(ply);

    // Write the resulting (re-coloured) point cloud to a PLY file.
    std::cout << "Writing PLY data to " << outputFile << std::endl;
    if (!ply.write(outputFile)) {
        std::cout << "Could not write PLY data to file " << outputFile << std::endl;
        return -2;
    }

    return 0;
}
