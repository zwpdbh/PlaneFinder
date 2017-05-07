#include "SimplePly.h"
#include <iostream>
#include <Eigen/Dense>

using namespace std;


Eigen::Vector3i generateRandomColor() {
    Eigen::Vector3i colourDefault(255, 255, 255);

    int rColor;
    int gColor;
    int bColor;

    // 255 will be the default colour for point
    do {
        rColor = rand() % 230 + 10;
        gColor = rand() % 230 + 10;
        bColor = rand() % 230 + 10;
    } while (rColor == 255 && gColor == 255 && bColor== 255);

    return Eigen::Vector3i(rColor, gColor, bColor);
}

int main(int argc, char *argv[]) {

    // Check the commandline arguments.
//  if (argc != 6) {
//    std::cout << "Usage: planeFinder <input file> <output file> <number of planes> <point-plane threshold> <number of RANSAC trials>" << std::endl;
//    return -1;
//  }
//  int nPlanes = atoi(argv[3]);
//  double threshold = atof(argv[4]);
//  int nTrials = atoi(argv[5]);

    int nPlanes = 5;
    double threshold = 0.02;
    double outlierRatio = 0.8;
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
    vector<int> dataSet;
    vector<bool> plyPointCheckedRecord;

    for (int k = 0; k < ply.size(); ++k) {
        dataSet.push_back(k);
        plyPointCheckedRecord.push_back(false);
    }


    for (int i = 0; i < nPlanes; ++i) {
        vector<long> bestInliers;
        vector<size_t> bestPlane;
        cout << endl;
        cout << "try to fit the " << i + 1 << "th plane..." << endl;
        cout << "take " << nTrials << " trails" << endl;
        cout << "dataSet size: " << dataSet.size() << endl;

        // repeat trials to find the best plane
        for (int r = 0; r < nTrials; ++r) {
            // 1. randomly take 3 points as my plane model
            vector<size_t> randomPlane;
            vector<long> inliers;

            while (randomPlane.size() < 3) {
                size_t sampleIndex = rand() % dataSet.size();
                // true if not present, false other wise
                if (find(randomPlane.begin(), randomPlane.end(), sampleIndex) == randomPlane.end()) {
                    randomPlane.push_back(sampleIndex);
                }
            }

            // 2. pick each point from data set to test if it is an inlier.
            for (int j = 0; j < dataSet.size(); ++j) {
                double d;
                Eigen::Vector3d p0 = ply[randomPlane[0]].location;
                Eigen::Vector3d p1 = ply[randomPlane[1]].location;
                Eigen::Vector3d p2 = ply[randomPlane[2]].location;

                Eigen::Vector3d u = p0 - p1;
                Eigen::Vector3d v = p2 - p1;
                Eigen::Vector3d norm = u.cross(v);
                Eigen::Vector3d normalized = norm / sqrt(norm.dot(norm));

                // pick each point from remained data set
                long index = dataSet[j];
                Eigen::Vector3d v0 = ply[index].location;
                d = fabs(normalized.dot(v0 - p1));

                // put the valid data into inlier
                if (d < threshold) {
                    inliers.push_back(index);
                }
            }

            // 3. evaluate the trial result
            cout << "" << endl;
            cout << r << "th trial evaluation result: " << (double) inliers.size() / dataSet.size()
                 << endl;
            if ((double) inliers.size() / dataSet.size() >
                (double) bestInliers.size() / dataSet.size()) {
                bestPlane = randomPlane;
                bestInliers = inliers;
            }
            cout << "current best plane evaluation: " << (double) bestInliers.size() / dataSet.size()
                 << endl;

            // clear the randomPlane
            randomPlane.clear();
            inliers.clear();

        } // end of repeat tails


        // update plane color, also update the data set index
        cout << "Before update data set, the current data set size is: " << dataSet.size() << endl;

        Eigen::Vector3i color = generateRandomColor();
        for (int k = 0; k < bestInliers.size(); ++k) {
            long index = bestInliers[k];
            ply[index].colour = color;
            plyPointCheckedRecord[index] = true;
//            dataSet.erase(
//                    std::remove(dataSet.begin(), dataSet.end(), index),
//                    dataSet.end());
//            cout << "Current data size: " << dataSet.size() << endl;
        }

        dataSet.clear();
        for (int l = 0; l < plyPointCheckedRecord.size(); ++l) {
            if (!plyPointCheckedRecord[l]) {
                dataSet.push_back(l);
            }
        }

        cout << "After update data set, the current data set size is: " << dataSet.size() << endl;

    }

    // Write the resulting (re-coloured) point cloud to a PLY file.
    std::cout << "Writing PLY data to " << outputFile << std::endl;
    if (!ply.write(outputFile)) {
        std::cout << "Could not write PLY data to file " << outputFile << std::endl;
        return -2;
    }

    return 0;
}
