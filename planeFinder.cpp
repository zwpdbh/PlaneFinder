//#include "SimplePly.h"
#include <iostream>
#include <Eigen/Dense>
#include "Plane.h"

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

    int nPlanes = 4;
    double threshold = 0.05;
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

    // put all Ply points' associated index as data set.
    int defaultColor = 107;
    Eigen::Vector3i colourDefault(defaultColor, defaultColor, defaultColor);
    vector<unsigned long> dataSetIndexes;
    for (unsigned long k = 0; k < ply.size(); ++k) {
        ply[k].colour = colourDefault;
        dataSetIndexes.push_back(k);
    }

    // begin RANSAC
    for (unsigned long i = 0; i < nPlanes; ++i) {
        Plane bestPlane;
        cout << endl;
        cout << "try to fit the " << i + 1 << "th plane..." << endl;
        cout << "take " << nTrials << " trails" << endl;

        // repeat trials to find the best plane
        for (int r = 0; r < nTrials; ++r) {
            // 1. randomly take 3 points as my plane model
            vector<unsigned long> randPoint;

            // randomly pick 3 point
            while (randPoint.size() < 3) {
                unsigned long sampleIndex = rand() % dataSetIndexes.size();
                // true if not present, false other wise
                if (find(randPoint.begin(), randPoint.end(), sampleIndex) == randPoint.end()) {
                    randPoint.push_back(sampleIndex);
                }
            }

            Plane plane(randPoint[0], randPoint[1], randPoint[2], ply);
            // 2. pick each point from data set to test if it is an inlier.
            for (int j = 0; j < dataSetIndexes.size(); ++j) {

                // pick each point from remained data set
                unsigned long index = dataSetIndexes[j];
                if (plane.isInlier(ply,index, threshold)) {
                    plane.inliers.push_back(index);
                    cout << plane.inliers.size() << endl;
                }
            }

            // 3. evaluate the trial result
            cout << "" << endl;
            cout << r << "th trial evaluation result: " << (double) plane.inliers.size() / dataSetIndexes.size()
                 << endl;
            if ((double) plane.inliers.size() / dataSetIndexes.size() >
                (double) bestPlane.inliers.size() / dataSetIndexes.size()) {
                bestPlane = plane;
            }
            cout << "current best plane evaluation: " << (double) bestPlane.inliers.size() / dataSetIndexes.size()
                 << endl;

            // clear the randPoint
            randPoint.clear();

        } // end of repeat tails


        // update plane color, also update the data set index
        cout << "Before update data set, the current data set size is: " << dataSetIndexes.size() << endl;

        for (int k = 0; k < bestPlane.inliers.size(); ++k) {
            long index = bestPlane.inliers[k];
            ply[index].colour = bestPlane.color;

        }

        dataSetIndexes.clear();
        for (i = 0; i < ply.size(); ++i) {
            Eigen::Vector3i pointColor = ply[i].colour;
            if (pointColor[0] == defaultColor && pointColor[1] == defaultColor && pointColor[2] == defaultColor) {
                dataSetIndexes.push_back(i);
            }
        }
        cout << "After update data set, the current data set size is: " << dataSetIndexes.size() << endl;

    }

    // Write the resulting (re-coloured) point cloud to a PLY file.
    std::cout << "Writing PLY data to " << outputFile << std::endl;
    if (!ply.write(outputFile)) {
        std::cout << "Could not write PLY data to file " << outputFile << std::endl;
        return -2;
    }

    return 0;
}
