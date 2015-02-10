//
//  main.cpp
//  PathFinding
//
//  Created by Uriana on 1/25/15.
//  Copyright (c) 2015 You Wu. All rights reserved.
//

#include <iostream>
#include <queue>
#include <stack>

#include "Problem.h"
#include "Node.h"


using namespace std;
struct compareDistance
{
    bool operator () ( const Node* a, const Node* b ) const
    {
        return a->hn > b->hn;
    }
};

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

/*
template <class T>
Node* search(T frontier, Node* init, int goal)
{
    //runtime log parameter
    int iter = 1;
    int frontierSize = 0;
    int* vertices = init->graph->vertices;
    
    vector<Node*> visited;
    visited.push_back(init);
    frontier.push(init);
    while (!frontier.empty()) {
        Node* testNode = nextElement(frontier);
        //Node* testNode = frontier.top();
        frontier.pop();
        
        //runtime log
        int testX, testY;
        testX = vertices[testNode->v*2];
        testY = vertices[testNode->v*2 + 1];
        float dist = testNode->hn;
        cout<<"iter="<<iter<<", frontier="<<frontier.size()
        <<", popped="<<testNode->v<<" ("<<testX<<", "<<testY<<"), depth="<<testNode->depth<<", dist2goal="<<dist << endl;
        
        
        if (testNode->v == goal) {
            
            cout << "=========="<<endl;
            cout << "total iterations = " <<iter<< endl;
            cout << "max frontier size = " << frontierSize << endl;
            cout << "vertices visited = "  << visited.size() << "/" << init->graph->nOfVertices<< endl;
            return testNode;
        }
        
        vector<Node*> children;
        children = testNode->successors();
        for (int i = 0; i < children.size(); i++) {
            bool hasVisited = false;
            for (int j = 0; j < visited.size(); j++) {
                if (children.at(i)->v == visited.at(j)->v)
                    hasVisited = true;
            }
            if (!hasVisited) {
                frontier.push(children.at(i));
                visited.push_back(children.at(i));
                
                frontierSize = max(frontierSize, (int)frontier.size());
                int index = children.at(i)->v;
                cout << "pushed "<<index<<" ("<<vertices[index*2]<<", "<<vertices[index*2+1]<<")"<<endl;

            }
        }
        iter++;
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
*/
int main(int argc, char * argv[])
{
    
    cout << "Choose from:" << endl;
    cout << "1. Random Problem generator  2.input file"<<endl;
    int choice;
    cin >> choice;
    cin.ignore(100, '\n');
    
    Problem *problem;
    if (choice == 1) {
        int nStack, nBlock;
        cout << "Stack number:";
        cin >> nStack;
        //cin.ignore(100, '\n');
        cout << "Block number:";
        cin >> nBlock;
        problem = new Problem(nStack, nBlock, 20);
    }else if (choice == 2) {
        char filename[256];
        cout << "Please enter file path: ";
        cin.getline (filename, 256);
        cout << "Loading " << filename << endl;
        problem = new Problem(filename);
    }else {
        cout << "Problem not correctly defined."<<endl;
        return 0;
    }
    cout << "problem hash string:" << problem->init->toString()<<endl;
    
    
    //init state log
    //cout << "Vertices = " << graph->nOfVertices << ", " << "edges = " << graph->nOfEdges << endl;
    //cout << "start = (" <<startX<<", "<<startY<<") , goal = ("<<endX<<", "<<endY<<"), vertices: "<<startI<<" and "<<endI<<endl;
    /*
    Node* init = new Node(startI);
    init->init(graph, endI);
    init->setHeur();
    Node* goal;
    
    priority_queue<Node*, vector<Node*>, compareDistance> GBFSfrontier;
    goal = search(GBFSfrontier, init, endI);
    
    
    vector<Node*> path = goal->traceback();

    cout << "path length = " << (int)path.size()-1 << endl;
    cout << "============="<<endl;
    cout << "Solution path: " << endl;
    for (int i = (int)path.size()-1; i >= 0; i--) {
        cout << "vertex "<< path.at(i)->v << " ("<<graph->vertices[path.at(i)->v*2]<<", "<<graph->vertices[path.at(i)->v*2+1]<<")"<<endl;
    }
    cout << "============="<<endl;
    */
    
    
    return 0;
}
