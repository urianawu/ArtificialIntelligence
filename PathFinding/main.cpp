//
//  main.cpp
//  PathFinding
//
//  Created by Uriana on 1/25/15.
//  Copyright (c) 2015 You Wu. All rights reserved.
//

#include <iostream>
#include "Graph.h"
using namespace std;

int main(int argc, char * argv[]) {
    
    char filename[256];
    cout << "Please enter a graph file: ";
    cin.getline (filename, 256);
    cout << "Loading " << filename << endl;

    Graph* graph = new Graph;
    graph->read(filename);
    return 0;
}
