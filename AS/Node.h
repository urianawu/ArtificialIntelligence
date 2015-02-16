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

using namespace std;

class Node{
public:
    //int v;
    int depth;
    float hn;
    Node* parent;
    
    string city;
    float* pos;
    
    Node(string, float*);
    Node(string, float*, Node*);
    
    void calculateHeur(int);
    //string toString();
    //void print();
    
    vector<Node*> successors(); //return neighbour
    vector<Node*> traceback(); // return path to root
private:
    //bool isAdjacent(char a, char b);
    
};
#endif /* defined(__PathFinding__Node__) */
