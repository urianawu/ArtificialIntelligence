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
#include <unordered_set>

#include "Problem.h"
#include "Node.h"


using namespace std;
class compare
{
    int heur;
public:
    compare(const int &heurParam = 1){heur = heurParam;}
    bool operator () ( const Node* a, const Node* b ) const
    {
        int afn, bfn;
        if(heur == 1){
            //blocks out of place
        afn = a->h1 + a->depth;
        bfn = b->h1 + b->depth;
        }else{
            //blocks out of order
        afn = a->h2 + a->depth;
        bfn = b->h2 + b->depth;
        }
        return afn > bfn;
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


template <class T>
Node* search(T frontier, Node* init, string goal)
{
    //runtime log parameter
    int iter = 1;
    int frontierSize = 0;
    
    unordered_set<string> visited;
    visited.emplace(init->toString());
    frontier.push(init);
    while (!frontier.empty()) {
        Node* testNode = nextElement(frontier);
        //Node* testNode = frontier.top();
        frontier.pop();
        
        //runtime log
        float fn = testNode->h1+ testNode->depth;
        cout<<"iter="<<iter<<", frontier="<<frontier.size()
        <<", f=g+h="<<fn << ", depth="<<testNode->depth<<endl;
        
        
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
                frontier.push(children.at(i));
                visited.emplace(children.at(i)->toString());
                
                frontierSize = max(frontierSize, (int)frontier.size());

            }
        }
        iter++;
    }
    
    return NULL;
}



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
        cout << "Block number:";
        cin >> nBlock;
        cout << "Stack number:";
        cin >> nStack;
        problem = new Problem(nStack, nBlock, 20);
    }else if (choice == 2) {
        char filename[256];
        cout << "Please enter file path: ";
        cin.getline (filename, 256);
        cout << "Loading " << filename <<"..."<< endl;
        problem = new Problem(filename);
    }else {
        cout << "Problem not correctly defined."<<endl;
        return 0;
    }
    
    int heur;
    cout << "heuristics: "<< endl;
    cout << "1. number of blocks out of place 2. number of adjacent blocks not in the correct order"<<endl;
    cin >> heur;
    
    //init state log
    cout << "=============="<<endl;
    cout << "initial state:"<<endl;
    problem->init->print();
    
    cout << "hash string:" << problem->init->toString()<<endl;

    
//    Node* init = new Node(startI);
//    init->init(graph, endI);
//    init->setHeur();
    Node* goalNode;
    string goalString(problem->goalString);
    priority_queue<Node*, vector<Node*>, compare> ASfrontier ((compare(heur)));
    goalNode = search(ASfrontier, problem->init, goalString);

    
    vector<Node*> path = goalNode->traceback();

    cout << "============="<<endl;
    cout << "Solution path: " << endl;
    for (int i = (int)path.size()-1; i >= 0; i--) {
        path.at(i)->print();
        cout << endl;
    }
    
    
    
    return 0;
}
