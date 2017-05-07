//
// Created by zwpdbh on 06/05/2017.
//

#include <iostream>
#include <math.h>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {

    vector<int> mydata;
    for (int i = 0; i < 10; ++i) {
        mydata.push_back( i * i);
    }

    vector<int> positions;
    for (int j = 0; j < 3; ++j) {
        positions.push_back( j + 1);
    }

    mydata.erase(mydata.begin() + positions[0]);


    return 0;
}