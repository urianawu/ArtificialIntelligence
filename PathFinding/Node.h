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
#include "Graph.h"
using namespace std;

class Node{
public:
    int v;
    int depth;
    float heur;
    Node* parent;
    static Graph* graph;
    
    void setGraph(Graph*); 
    Node(int, Node*);
    
    vector<Node*> successors(); //return neighbour
    vector<Node*> traceback(); // return path to root
    
};
#endif /* defined(__PathFinding__Node__) */
