//
//  Node.h
//  PathFinding
//
//  Created by Uriana on 1/28/15.
//  Copyright (c) 2015 You Wu. All rights reserved.
//

#ifndef __Search__Node__
#define __Search__Node__

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
    
    vector<stack<char>> state;
    
    Node(vector<stack<char>>);
    Node(vector<stack<char>>, Node*);
    
    void calculateHeur(int);
    string toString();
    void print();
    
    vector<Node*> successors(); //return neighbour
    vector<Node*> traceback(); // return path to root
private:
    bool isAdjacent(char a, char b);
    
};
#endif /* defined(__PathFinding__Node__) */
