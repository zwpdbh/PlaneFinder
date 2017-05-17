//
// Created by zwpdbh on 16/05/2017.
//

#include "RANSAC.h"
#include <iostream>

using namespace std;

int updateNumOfTrials(double successfulRate, double outlierRatio, int minNumOfSampleNeeded) {
    return (int) (log(1 - successfulRate) / log(1 - pow((1 - outlierRatio), minNumOfSampleNeeded)));
}

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


RANSAC::RANSAC(int nPlanes, double threshold, double expectedOutlierRatio, double expectedSuccessfulRate) {
    this->nPlanes = nPlanes;
    this->threshold = threshold;
    this->expectedOutlierRatio = expectedOutlierRatio;
    this->expectedSuccessfulRate = expectedSuccessfulRate;

}

void RANSAC::fitPlyPoints(SimplePly &ply) {

    int nTrials = (int) (log(1 - this->expectedSuccessfulRate) / log(1 - pow((1 - this->expectedOutlierRatio), 3)));

    std::cout << "Searching for " << this->nPlanes << " planes" << std::endl;
    std::cout << "Using a point-plane threshold of " << this->threshold << " units" << std::endl;
    std::cout << "Applying RANSAC with " << nTrials << " trials" << std::endl;

    unsigned long totalSize = ply.size();
    unsigned long fittedSize = 0;
    std::cout << "Read " << totalSize << " points" << std::endl;


    // put all Ply points' associated index as data set.
    unordered_map<long, PlyPoint *> dataSet;
    for (long i = 0; i < totalSize; i++) {
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

    int i = 0;
    while ((double) fittedSize / totalSize < 0.95 || i < nPlanes) {
        vector<long> bestInliers;
        Plane bestPlane;
        nTrials = updateNumOfTrials(this->expectedSuccessfulRate, this->expectedOutlierRatio, 3);
        cout << endl;
        cout << "try to fit the " << i + 1 << "th plane..." << endl;
        cout << "take " << nTrials << " trails" << endl;

        // repeat trials to find the best plane
        for (int r = 0; r < nTrials; ++r) {
            // 1. randomly take 3 points as my plane model
            vector<PlyPoint *> randomPoints = getRandomPoints(&dataSet);

            Plane currentPlane(randomPoints[0], randomPoints[1], randomPoints[2]);
            vector<long> currentInliers = currentPlane.fitPlane(dataSet, this->threshold);

            if (currentInliers.size() > bestInliers.size()) {
                bestInliers = currentInliers;
                bestPlane = currentPlane;

                double inlierRatio = (double) bestInliers.size() / dataSet.size();
                double updatedOutlierRatio = 1 - inlierRatio;
                cout << "" << endl;
                cout << "update best plane evaluation: " << inlierRatio << endl;
                nTrials = updateNumOfTrials(this->expectedSuccessfulRate, updatedOutlierRatio, 3);
                cout << "update outlier ratio: " << updatedOutlierRatio << endl;
                cout << "Update nTrials to: " << nTrials << endl;
            }

        }

        planes.push_back(bestPlane);
        i += 1;
        fittedSize += bestPlane.inliers.size();

        // update plane color, also get rid of the fitted plane points
        cout << "the current bestInliers' size is: " << bestInliers.size() << endl;
        cout << "Before update data set, the current data set size is: " << dataSet.size() << endl;

        Eigen::Vector3i colour = colours[i % colours.size()];
        for (auto const each: bestInliers) {
            dataSet[each]->colour = colour;
            dataSet.erase(each);
        }
        cout << "Fitted " << (double) fittedSize / totalSize << " of total points" << endl;
        cout << "After update data set, the rest data set size is: " << dataSet.size() << endl;
    } // end of RANSAC fitting

    // summary
    cout << endl;
    cout << "Fit total " << planes.size() << " planes, their size are: " << endl;
    for (int i = 0; i < planes.size(); ++i) {
        cout << "plane " << i+1 << " size: " << planes[i].inliers.size() << endl;
    }
    cout << "Total points size: " << totalSize << ", fitted points " << fittedSize << " , percentage = " << (double) fittedSize / totalSize << endl;

}
