//
//  Node.h
//  PathFinding
//
//  Created by Uriana on 1/28/15.
//  Copyright (c) 2015 You Wu. All rights reserved.
//

#ifndef __AS__Node__
#define __AS__Node__

#include <stdio.h>
#include <vector>
#include <stack>
#include <string>
#include <math.h>
#include <iostream>

#include "SearchSpace.h"
using namespace std;

class Node{
public:
    //int v;
    int depth;
    double value;
    Node* parent;
    
    cityMap state;
    
    Node(cityMap);
    Node(cityMap, Node*);
    
    double distance(cityMap);
    //void print();
    
    vector<Node*> successors(); //return neighbour
    vector<Node*> traceback(); // return path to root
private:
    double degreeToRad(double);
    //bool isAdjacent(char a, char b);
    
};
#endif /* defined(__PathFinding__Node__) */
