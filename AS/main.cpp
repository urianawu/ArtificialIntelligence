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

#include "SearchSpace.h"
#include "Node.h"


using namespace std;
//GET frontier next element
//slightly different for queue and stack
/*template <class T>
Node* nextElement(T frontier)
{
    return frontier.top(); // for stack and priority_queue
}

template<> Node* nextElement(queue<Node*> frontier)
{
    return frontier.front(); //for stack
}


template <class T>
Node* search(T frontier, Node* init, string goal, int heur)
{
    //runtime log parameter
    int iter = 1;
    int frontierSize = 0;
    
    unordered_set<string> visited;
    visited.emplace(init->toString());
    frontier.push(init);
    while (!frontier.empty()) {
        Node* testNode = nextElement(frontier);

        frontier.pop();
        
        //runtime log
        float fn = testNode->hn + testNode->depth;
        cout<<"iter="<<iter<<", frontier="<<frontier.size()
        <<", f=g+h="<<fn <<", h="<<testNode->hn<< ", depth="<<testNode->depth<<endl;
        
        if (testNode->toString() == goal) {
            
            cout << "=========="<<endl;
            cout << "Success!"<<endl;
            cout << "depth(path length) = "<<testNode->depth<<endl;
            cout << "total iterations(goal tests) = " <<iter<< endl;
            cout << "max queue size = " << frontierSize << endl;
            
            return testNode;
        }
        
        vector<Node*> children;
        children = testNode->successors();
        for (int i = 0; i < children.size(); i++) {
            bool hasVisited = false;
            unordered_set<string>::const_iterator got = visited.find (children.at(i)->toString());
            if ( got != visited.end() ) {
                hasVisited = true;
            }
            if (!hasVisited) {
                children.at(i)->calculateHeur(heur);
                frontier.push(children.at(i));
                visited.emplace(children.at(i)->toString());
                
                frontierSize = max(frontierSize, (int)frontier.size());
                if (frontierSize > 100000) {
                    exit(EXIT_FAILURE);
                }

                
            }
        }
        iter++;
    }
    
    return NULL;
}

*/
float schedule(int t)
{
    if (30 - 0.00001*t > 0) {
        return 30 - 0.00001*t;
    }else
        return 0;
}
/*
Node* simulatedAnnealing(cityMap map)
{
    Node* current = new Node(map);
    for (int t = 1; t < 1000000; t++) {
        float T = schedule(t);
        if (T == 0) {
            return current;
        }
        Node* next = (current->successors()).at(rand()/RAND_MAX);
        float deltaE = next->value - current->value;
        if (deltaE > 0) {
            current = next;
        }else {
            srand((int)time(NULL));
            float randomNumber = (double)rand() / RAND_MAX;
            float prob = exp(deltaE/T);
            if (randomNumber <= prob) {
                current = next;
            }
        }
    }
    return NULL;
    
}
*/
int main(int argc, char * argv[])
{
    
    SearchSpace* txMap = new SearchSpace;
    char dataFile[80] = "texas-cities.dat";
    txMap->read(dataFile);
    cout << "loading "<<dataFile<<endl;
    Node* current = new Node(txMap->txCities);

    
////    Node* init = new Node(startI);
////    init->init(graph, endI);
////    init->setHeur();
//    Node* goalNode;
//    string goalString(problem->goalString);
//    priority_queue<Node*, vector<Node*>, compare> ASfrontier;
//    goalNode = search(ASfrontier, problem->init, goalString, heur);
//
//    
//    vector<Node*> path = goalNode->traceback();

//    cout << "============="<<endl;
//    cout << "Solution path: " << endl;
//    for (int i = (int)path.size()-1; i >= 0; i--) {
//        path.at(i)->print();
//        cout << endl;
//    }
//    
    
    
    return 0;
}