#include "SimplePly.h"
#include <iostream>
#include <Eigen/Dense>

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
    double threshold = 0.1;
    double outlierRatio = 0.70;
    double successfulRate = 0.9;
    int minNumOfSampleNeeded = 3;
    int nTrials = (int) (log(1 - successfulRate) / log(1 - pow((1 - outlierRatio), minNumOfSampleNeeded)));

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


    //
    vector<int> currentDataSetIndexes;
    for (int k = 0; k < ply.size(); ++k) {
        currentDataSetIndexes.push_back(k);
    }



    for (int i = 0; i < 1; ++i) {
        vector<long> bestInliers;
        vector<size_t > bestPlane;

        // repeat trials to find the best plane
        cout << "take " << nTrials  << " trails" << endl;
        for (int r = 0; r < nTrials; ++r) {
            // 1. randomly take 3 points as my plane model
            vector<size_t> randomPlane;
            vector<long> inliers;

            while(randomPlane.size() <3 ) {
                size_t sampleIndex = rand() % currentDataSetIndexes.size();
                // true if not present, false other wise
                if (find(randomPlane.begin(), randomPlane.end(), sampleIndex) == randomPlane.end()) {
                    randomPlane.push_back(sampleIndex);
                }
            }

            // 2. pick each point from data set to test if it is an inlier.
            for (int j = 0; j < currentDataSetIndexes.size(); ++j) {
                double d;
                Eigen::Vector3d p0 = ply[randomPlane[0]].location;
                Eigen::Vector3d p1 = ply[randomPlane[1]].location;
                Eigen::Vector3d p2 = ply[randomPlane[2]].location;

                Eigen::Vector3d u = p0 - p1;
                Eigen::Vector3d v = p2 - p1;
                Eigen::Vector3d norm = u.cross(v);
                Eigen::Vector3d normalized = norm / sqrt(norm.dot(norm));

                // pick each point from remained data set
                long index = currentDataSetIndexes[j];
                Eigen::Vector3d v0 = ply[index].location;
                d = fabs(normalized.dot(v0 - p1));

                // put the valid data into inlier
                if (d < threshold) {
                    inliers.push_back(index);
                }
            }

            // 3. evaluate the trial result
            cout << r <<"th trial evaluation result: " << (double) inliers.size() / currentDataSetIndexes.size() << endl;
            if ((double) inliers.size() / currentDataSetIndexes.size() > (double) bestInliers.size() / currentDataSetIndexes.size()) {
                bestPlane = randomPlane;
                bestInliers = inliers;
            }
            cout << "current best plane evaluation: " << (double) bestInliers.size() / currentDataSetIndexes.size() << endl;

            // clear the randomPlane
            randomPlane.clear();
            inliers.clear();

        } // end of repeat tails

        // output best plane
        Eigen::Vector3i colour(255, 0, 0);
        for (int k = 0; k < bestInliers.size(); ++k) {
            long index = bestInliers[k];
            ply[index].colour = colour;
        }

        // update data set, find next plane in the rest data set

    }


//    // update color stuff
//
//    // Recolour points - here we are just doing colour based on index
//    std::cout << "Recolouring points" << std::endl;
//    std::vector<Eigen::Vector3i> colours;
//    colours.push_back(Eigen::Vector3i(255, 0, 0));
//    colours.push_back(Eigen::Vector3i(0, 255, 0));
//    colours.push_back(Eigen::Vector3i(0, 0, 255));
//    // Can add more colours as needed
//
//    // each planeSize holds the number of points = total / num of plane
//    size_t planeSize = ply.size() / nPlanes;
//
//    for (size_t index = 0; index < ply.size(); ++index) {
//        size_t indexInPlane = index / planeSize;
//        size_t colourIx = indexInPlane % colours.size(); // May need to recycle colours
//        ply[index].colour = colours[colourIx];
//    }
//
    // Write the resulting (re-coloured) point cloud to a PLY file.
    std::cout << "Writing PLY data to " << outputFile << std::endl;
    if (!ply.write(outputFile)) {
        std::cout << "Could not write PLY data to file " << outputFile << std::endl;
        return -2;
    }

    return 0;
}
