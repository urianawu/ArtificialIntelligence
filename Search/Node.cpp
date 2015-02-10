//
//  Node.cpp
//  PathFinding
//
//  Created by Uriana on 1/28/15.
//  Copyright (c) 2015 You Wu. All rights reserved.
//

#include "Node.h"


Node::Node(vector<stack<char>> state)
{
    //v = i;
    parent = NULL;
    depth = 0;
    this->state = state;
}

Node::Node(vector<stack<char>> state, Node *p)
{
    //v = i;
    parent = p;
    depth = p->depth + 1;
    this->state = state;
    setHeur();
}

void Node::setHeur()
{
    int goalX, goalY, X, Y;
    /*
    goalX = graph->vertices[goalI*2];
    goalY = graph->vertices[goalI*2+1];
    X = graph->vertices[v*2];
    Y = graph->vertices[v*2+1];
    hn = sqrtf(powf(abs(goalX - X),2.0) + powf(abs(goalY - Y),2.0));
     */
}
string Node::toString()
{
    string hashString = "";
    vector<stack<char>> tmp = state;
    for (int i = 0; i < tmp.size(); i++) {
        while (!tmp.at(i).empty()) {
            hashString+=tmp.at(i).top();
            tmp.at(i).pop();

        }
        hashString+="#";
    }
    return hashString;
}

vector<Node*> Node::successors()
{
    vector<Node*> nodes;
    //loop through each pair of stacks
    for (int i = 0; i < state.size(); i++) {
        for (int j = 0; j < state.size(); j++) {
            if (i != j && !state.at(i).empty()) {
                //pick one block on stack i and put on stack j
                vector<stack<char>> tmp = state;
                tmp.at(j).push(tmp.at(i).top());
                tmp.at(i).pop();
                //set new successor node
                nodes.push_back(new Node(tmp, this));
            }
        }
    }
    /*
    for (int i = 0; i < graph->nOfEdges * 2; i+=2) {
        if (graph->edges[i] == v){
            //cout << "i: " << i <<" v 0 x ||" << v << " | "<< graph->edges[i]<<" | "<< graph->edges[i+1]  << endl;

            nodes.push_back(new Node(graph->edges[i+1], this));
        }
        if(graph->edges[i+1] == v){
            //cout << "i: " << i << " x 0 v ||" << graph->edges[i] << " | " <<graph->edges[i+1]<<" | "<< v << endl;

            nodes.push_back(new Node(graph->edges[i], this));
            //cout << "i-1 : " << i;
        }
    }
     */
    return nodes;
    
}

vector<Node*> Node::traceback()
{
    vector<Node*> nodes;
    nodes.push_back(this);
    
    Node* predecessor;
    predecessor = parent;
    while (predecessor != NULL) {
        nodes.push_back(predecessor);
        predecessor = predecessor->parent;
    }
    return nodes;
}