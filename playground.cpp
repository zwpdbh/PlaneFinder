//
// Created by zwpdbh on 06/05/2017.
//

#include "Cluster.h"
#include <iostream>
#include <map>
#include <unordered_map>

using namespace std;


int main(int argc, char *argv[]) {
    unordered_map<long, string> data;
    
    data[0] = "a";
    data[1] = "b";
    data[2] = "c";
    
    cout << data.size() << endl;
    
    data.erase(0);
    data.erase(1);
    cout << data.size() << endl;
    
    data[1] = "c";
    cout << data.size() << endl;

    return 0;
}