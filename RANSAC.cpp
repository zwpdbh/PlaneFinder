//
// Created by zwpdbh on 16/05/2017.
//

#include "RANSAC.h"
#include <iostream>

using namespace std;

/**
 * Helper function, update the number of trials based on parameters
 * @param successfulRate is the probability of success
 * @param outlierRatio is the proortion of outlier / current data set
 * @param minNumOfSampleNeeded will be set to 3 which means use 3 samples to represent my model which is a plane
 * @return the updated number of trials
 */
int updateNumOfTrials(double successfulRate, double outlierRatio, int minNumOfSampleNeeded) {
    return (int) (log(1 - successfulRate) / log(1 - pow((1 - outlierRatio), minNumOfSampleNeeded)));
}

/**
 * get a 3 random points for forming the random plane from data set
 * @param dataSet randomly pick 3 points from this data Set
 */
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

/**
 * constructor
 * @param nPlanes specify the number of planes to fit
 * @param threshold test the distance from a point to this plane, if the distance is smaller
 *  than this threshold, it will be considered as inliers of this plane
 * @param expectedOutlierRatio it represent the number of outliers in the data set, it will be updated in the process
 *  of different trials
 * @param expectedSuccessfulRate the probability of expected successuful rate
 */
RANSAC::RANSAC(int nPlanes, double threshold, double expectedOutlierRatio, double expectedSuccessfulRate) {
    this->nPlanes = nPlanes;
    this->threshold = threshold;
    this->expectedOutlierRatio = expectedOutlierRatio;
    this->expectedSuccessfulRate = expectedSuccessfulRate;

}


/**
 * RANSAC fitting function, use RANSAC to fit some planes in the SimplePly data set with
 * parameters initialized during initialization
 * @param ply the data Set.
 */
void RANSAC::fitPlyPoints(SimplePly &ply) {

    // get the initial number of trials based on parameters
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

    // create different colours for
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


    // planes will hold the fitted planes
    vector<Plane> planes;

    int i = 0;

    // the fitting process will be stopped when either:
    // the founded total planes' points / total points >= 0.95
    // or when the number of fitted plane is > specified nPlanes
    while ((double) fittedSize / totalSize < 0.95 && i < nPlanes) {
        // hold the best results which is the fitted points
        vector<long> bestInliers;

        // hold the best plane
        Plane bestPlane;

        // the number of trials for fitting one plane
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

            // 2. update fitting results when it is better than the current one.
            if (currentInliers.size() > bestInliers.size()) {
                bestInliers = currentInliers;
                bestPlane = currentPlane;

                // compute the outlier ratio based on the fitting result
                double inlierRatio = (double) bestInliers.size() / dataSet.size();
                double updatedOutlierRatio = 1 - inlierRatio;
                cout << "" << endl;
                cout << "update best plane evaluation: " << inlierRatio << endl;
                // update the number of trials each time we find a better inlierRatio
                nTrials = updateNumOfTrials(this->expectedSuccessfulRate, updatedOutlierRatio, 3);
                cout << "update outlier ratio: " << updatedOutlierRatio << endl;
                cout << "Update nTrials to: " << nTrials << endl;
            }

        }

        // after those trials, save the fitted plane into planes
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
