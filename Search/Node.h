//
//  Node.h
//  PathFinding
//
//  Created by Uriana on 1/28/15.
//  Copyright (c) 2015 You Wu. All rights reserved.
//

#ifndef __PathFinding__Node__
#define __PathFinding__Node__

#include <stdio.h>
#include <vector>
#include <math.h>

#include "Graph.h"
using namespace std;

class Node{
public:
    int v;
    int depth;
    float hn;
    Node* parent;
    static Graph* graph;
    static int goalI;
    
    Node(int);
    Node(int, Node*);
    
    void init(Graph*, int);
    void setHeur();

    vector<Node*> successors(); //return neighbour
    vector<Node*> traceback(); // return path to root
    
};
#endif /* defined(__PathFinding__Node__) */
