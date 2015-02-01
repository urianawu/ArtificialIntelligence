//
//  main.cpp
//  PathFinding
//
//  Created by Uriana on 1/25/15.
//  Copyright (c) 2015 You Wu. All rights reserved.
//

#include <iostream>
#include "Node.h"
#include <queue>
#include <stack>

using namespace std;

//GET frontier next element
//slightly different for queue and stack
template <class T>
Node* nextElement(T frontier)
{
    return frontier.top(); // for stack and priority_queue
}

template<> Node* nextElement(queue<Node*> frontier)
{
    return frontier.front(); //for stack
}


template <class T>
Node* search(T frontier, Node* init, int goal)
{
    vector<Node*> visited;
    visited.push_back(init);
    frontier.push(init);
    while (!frontier.empty()) {
        Node* testNode = nextElement(frontier);
        //Node* testNode = frontier.top();
        frontier.pop();
        if (testNode->v == goal) {
            return testNode;
        }
        visited.push_back(testNode);
        
        vector<Node*> children;
        children = testNode->successors();
        for (int i = 0; i < children.size(); i++) {
            if (find(visited.begin(), visited.end(), children.at(i)) == visited.end())
            {
                frontier.push(children.at(i));
            }
        }
    }
    return NULL;
}


int getVertexIndex(int x, int y, Graph* g)
{
    int index = -1;
    for (int i = 0; i < g->nOfVertices*2; i+=2) {
        if (x == g->vertices[i] && y == g->vertices[i+1]) {
            index = i/2;
        }
    }
    return index;
}

int main(int argc, char * argv[])
{
    
    char filename[256];
    //    cout << "Please enter a graph file: ";
    //    cin.getline (filename, 256);
    //    cout << "Loading " << filename << endl;
    
    Graph* graph = new Graph;
    graph->read("ATM.graph");
    
    char searchAlgorithm[256];
    int startX, startY, endX, endY;
    cout << "BFS | DFS | GBFS :";
    cin.getline(searchAlgorithm, 256);
    
    cout << "start point: ";
    scanf ("%d %d",&startX, &startY);
    
    cout << "end point: ";
    scanf("%d %d", &endX, &endY);
    
    int startI = getVertexIndex(startX, startY, graph);
    if (startI == -1) {
        cout << "start point not found!"<<endl;
        return 0;
    }
    
    int endI = getVertexIndex(endX, endY, graph);
    if (endI == -1) {
        cout << "goal point not found in graph!" << endl;
        return 0;
    }
    
    Node* init = new Node(startI, NULL);
    init->setGraph(graph);
    Node* goal;
    
    switch (searchAlgorithm[0]) {
        case 'B':
        case 'b':
        {
            queue<Node*> BFSfrontier;
            goal = search(BFSfrontier, init, endI);
            break;
        }
        case 'D':
        case 'd':
        {
            stack<Node*> DFSfrontier;
            goal = search(DFSfrontier, init, endI);
            break;
        }
        case 'G':
        case 'g':
        {
            priority_queue<Node*> GBFSfrontier;
            goal = search(GBFSfrontier, init, endI);
            break;
        }
        default:
            cout << "Algorithm not correctly defined, please choose from: BFS / DFS / GBFS." << endl;
            return 0;
            break;
    }
    
    
    cout << "Solution path: " << endl;
    vector<Node*> path = goal->traceback();
    for (int i = path.size()-1; i >= 0; i--) {
        cout << path.at(i)->v << " | ";
    }
    cout << "search algorithm = " << searchAlgorithm;
    cout << "total iterations = ";
    
    return 0;
}
