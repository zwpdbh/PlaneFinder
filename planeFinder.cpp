#include <iostream>
#include "SimplePly.h"
#include "Plane.h"


using namespace std;

/**
 * randomly get 3 points from my data for form a plane
 * @param dataPoints is the total data
 * @param minNumOfSampleNeeded the minimum number of data to form my model, a plane need 3 data points
 */
vector<PlyPoint> getRandomSampleFromDataPoints(vector<PlyPoint> dataPoints, int minNumOfSampleNeeded) {
    vector<PlyPoint> randomSample;
    vector<unsigned long> randomIndex;
    unsigned long size = dataPoints.size();

    while (randomIndex.size() <= minNumOfSampleNeeded) {
        unsigned long sampleIndex = rand() % size;
        // true if not present, false other wise
        if (find(randomIndex.begin(), randomIndex.end(), sampleIndex) == randomIndex.end()) {
            randomIndex.push_back(sampleIndex);
        }
    }

    for (int i = 0; i < randomIndex.size(); ++i) {
        randomSample.push_back(dataPoints[randomIndex[i]]);
    }
    return randomSample;
}


/**
 * Use RANSAC to fit a plane, return all the inlier points of a plane
 * @param dataPoints the data will be fit
 * @param outlierRatio the prior probability of outlier in data
 * @param successfulProbability the expected successful probability to find a good fit
 * @param threshold the threshold which is the distance of a point to the plane
 */
vector<int> findPlaneDataPointViaRANSAC(vector<PlyPoint> dataPoints, double outlierRatio, double successfulProbability, double threshold) {
    vector<int> planePointsIndexes;
    int minNumOfSampleNeeded = 3;
    int trialsNeeded = (int) (log(1 - successfulProbability) / log(1 - pow((1 - outlierRatio), minNumOfSampleNeeded)));

    vector<int> inliers;
    int totalSize = dataPoints.size();
    double evaluation = 0;

    for (int i = 0; i < trialsNeeded; ++i) {
        // 1. get 3 random points for model my plane
        vector<PlyPoint> samples = getRandomSampleFromDataPoints(dataPoints, 3);
        Plane p(samples[0], samples[1], samples[2]);

        // 2. use my model to test the data
        inliers = p.getInliersIndex(dataPoints, threshold);

        // 3. evaluate the data based on my model, update my inliers when the ratio of inlier is better than previous.
        if (inliers.size() / totalSize > evaluation) {
            evaluation = inliers.size() / totalSize;
            planePointsIndexes = inliers;
        }
    }
    
    return planePointsIndexes;
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

//    // each planeSize holds the number of points = total / num of plane
//    size_t planeSize = ply.size() / nPlanes;
//    for (size_t index = 0; index < ply.size(); ++index) {
//        size_t indexInPlane = index / planeSize;
//        size_t colourIx = indexInPlane % colours.size(); // May need to recycle colours
//        ply[index].colour = colours[colourIx];
//    }



    // Write the resulting (re-coloured) point cloud to a PLY file.
    std::cout << "Writing PLY data to " << outputFile << std::endl;
    if (!ply.write(outputFile)) {
        std::cout << "Could not write PLY data to file " << outputFile << std::endl;
        return -2;
    }

    return 0;
}
