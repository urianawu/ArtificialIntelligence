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


template <class T>
Node* search(T frontier, Node* init, int goal)
{
    vector<Node*> visited;
    visited.push_back(init);
    frontier.push(init);
    while (!frontier.empty()) {
        Node* testNode = frontier.front();
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

//Node* Search(char* algorithm, Node* init, int* goal)
//{
//    
//    switch (algorithm[0]) {
//        case 'B':
//            queue<Node*> frontier; //tbd
//        break;
//            case 'D':
//            break;
//            case 'G':
//            break;
//            
//        default:
//            cout << "Algorithm not correctly defined, please choose from: BFS / DFS / GBFS." << endl;
//            break;
//    }
//    
//}

int main(int argc, char * argv[]) {
    
    char filename[256];
//    cout << "Please enter a graph file: ";
//    cin.getline (filename, 256);
//    cout << "Loading " << filename << endl;

    Graph* graph = new Graph;
    graph->read("ATM.graph");
    
    Node* init = new Node(0, NULL);
    init->setGraph(graph);
    
    queue<Node*> BFSfrontier;
    Node* goal = search(BFSfrontier, init, 21);
    cout << "solution: " << endl;
    vector<Node*> path = goal->traceback();
    for (int i = 0; i < path.size(); i++) {
        cout << path.at(i)->v << " | ";
    }
    return 0;
}
