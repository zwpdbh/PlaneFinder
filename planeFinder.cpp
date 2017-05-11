
#include <iostream>
#include "Plane.h"

using namespace std;

vector<PlyPoint *> getRandomPoints(unordered_map<long, PlyPoint *> *dataSet) {
    vector<PlyPoint *> randomPoints;

    vector<unsigned long> randomIndexes;
    while (randomIndexes.size() < 3) {
        unsigned long  sampleIndex = rand() % dataSet->size();
        if (find(randomIndexes.begin(), randomIndexes.end(), sampleIndex) == randomIndexes.end()) {
            randomIndexes.push_back(sampleIndex);
        }
    }

    for (unsigned long const index: randomIndexes) {
        auto it = dataSet->begin();
        advance(it, index);
        randomPoints.push_back(it->second);
    }

    return randomPoints;
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
    double threshold = 0.05;
    double outlierRatio = 0.65;
    double successfulRate = 0.95;
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
    unordered_map<long, PlyPoint *> dataSet;
    for (long i = 0; i < ply.size(); i++) {
        dataSet[i] = &ply[i];
    }

    vector<Eigen::Vector3i> colours;
    for (int i = 0; i < 8; i++) {
        colours.push_back(Eigen::Vector3i(204, 51, 255));
        colours.push_back(Eigen::Vector3i(255, 102, 102));
        colours.push_back(Eigen::Vector3i(230, 0, 172));
        colours.push_back(Eigen::Vector3i(255, 255, 0));
        colours.push_back(Eigen::Vector3i(0, 204, 0));
        colours.push_back(Eigen::Vector3i(198, 140, 83));
        colours.push_back(Eigen::Vector3i(153, 204, 255));
    }

    vector<Plane> planes;


    for (int i = 0; i < nPlanes; ++i) {
        vector<long> bestInliers;
        Plane bestPlane;
        cout << endl;
        cout << "try to fit the " << i + 1 << "th plane..." << endl;
        cout << "take " << nTrials << " trails" << endl;

        // repeat trials to find the best plane
        for (int r = 0; r < nTrials; ++r) {

            // 1. randomly take 3 points as my plane model
            vector<PlyPoint *> randomPoints = getRandomPoints(&dataSet);

            Plane currentPlane(randomPoints[0], randomPoints[1], randomPoints[2]);
            vector<long> currentInliers = currentPlane.fitPlane(dataSet, 0.05);

            if (currentInliers.size() > bestInliers.size()) {
                bestInliers = currentInliers;
                bestPlane = currentPlane;
            }

            // 3. evaluate the trial result
            cout << "" << endl;
            cout << r << "th trial evaluation result: " << (double) currentInliers.size() / dataSet.size()
                 << endl;
            cout << "current best plane evaluation: " << (double) bestInliers.size() / dataSet.size()
                 << endl;

        }


        planes.push_back(bestPlane);

        // update plane color, also update the data set index
        cout << "the current bestInliers' size is: " << bestInliers.size() << endl;
        cout << "Before update data set, the current data set size is: " << dataSet.size() << endl;

        Eigen::Vector3i colour = colours[i];
        for (auto const each: bestInliers) {
            dataSet[each]->colour = colour;
            dataSet.erase(each);
        }

        cout << "After update data set, the current data set size is: " << dataSet.size() << endl;
    }


    cout << "Fit total " << planes.size() << " planes, their size are: " << endl;
    for (int i = 0; i < planes.size(); ++i) {
        cout << "plane " << i+1 << " size: " << planes[i].inliers.size() << endl;
    }

    // Write the resulting (re-coloured) point cloud to a PLY file.
    std::cout << "Writing PLY data to " << outputFile << std::endl;
    if (!ply.write(outputFile)) {
        std::cout << "Could not write PLY data to file " << outputFile << std::endl;
        return -2;
    }

    return 0;
}
