//
// Created by zwpdbh on 06/05/2017.
//

#include <iostream>
#include <math.h>
#include <Eigen/Core>
#include <Eigen/Dense>

using namespace std;

int main(int argc, char *argv[]) {

    cout << pow(2, 5) << endl;

    Eigen::Vector3d u(1, 1, 1);
    Eigen::Vector3d v(2, 3, 4);
    Eigen::Vector3d w(v-u);

    cout << w << endl;
    cout << w[0] << endl;
    cout << w[1] << endl;
    cout << w[2] << endl;

//    cout << u.cross3(v) << endl;
    cout << u.cross(v) << endl;

    return 0;
}