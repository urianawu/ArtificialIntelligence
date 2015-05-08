//
//  main.cpp
//  PathFinding
//
//  Created by Uriana on 1/25/15.
//  Copyright (c) 2015 You Wu. All rights reserved.
//

#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

#include "KbReader.h"
#include "OperatorGenerator.h"
#include "OperatorReader.h"

using namespace std;
int iteration = 0;

struct Node{
    vector<string> goals;
    vector<string> plan;
};

struct compareDistance
{
    bool operator () ( const Node* a, const Node* b ) const
    {
        return a->plan.size() > b->plan.size();
    }
};

vector<string> regress(vector<string> goals, Operator* oper)
{
    vector<string> newgoals;
    for (auto it : goals) {
        bool foundInAddList = false;
        for (auto jt : oper->getAddList()) {
            if (it == jt) {
                foundInAddList = true;
            }
        }
        if (!foundInAddList) {
            newgoals.push_back(it);
        }
    }
    for (auto it : oper->getPrecond()) {
        newgoals.push_back(it);
    }
    
    return newgoals;

}

string toString(vector<string> strVec)
{
    string str;
    for (auto it : strVec) {
        str += it;
        
    }
    return str;
}


vector<string> goalRegression(vector<string> goals, vector<Operator*> opers, vector<string> kb)
{
    
    priority_queue<Node*, vector<Node*>, compareDistance> q;

    Node* n = new Node;
    n->goals = goals;
    q.push(n);
    
    map<string,int> visited;

    
    
    while (1) {
        iteration++;

        Node* node = new Node;
        node->goals = q.top()->goals;
        node->plan = q.top()->plan;

        cout<<"\niter="<<iteration<<", queue="<<q.size()<<endl;
        
        q.pop();
        
        
        bool allGoalsSatisfied = true;
        for (auto it: node->goals) {
            bool found = false;
            for (auto jt : kb) {
                if (it == jt) {
                    found = true;
                }
            }
            if (!found) {
                allGoalsSatisfied = false;
            }
        }
        if (allGoalsSatisfied) {
            cout << "Solution found!"<<endl;
            cout << "plan:"<<endl;
            for (auto p : node->plan) {
                cout << p<<endl;

            }
            
            cout<<endl;
            return node->plan;
        }
        
        cout<<"context:";
        for (auto p : node->plan) {
            cout << p;
            if (p != node->plan.back()) {
                cout<<" ";
            }
        }
        
        cout<<endl;
        
        cout<<"goal stack: ";
        for (auto g : node->goals) {
            cout << g;
            if (g != node->goals.back()) {
                cout<<" ";
            }
        }
        cout<<endl;

        
        for (int i = 0 ; i < node->goals.size() ; i++) {
        for (auto oper : opers) {
            bool operRelevant = false;
            bool consistent = true;
            
            for (auto add : oper->getAddList()) {
                if (node->goals[i] == add) {
                    operRelevant = true;
                }
            }
            
            for (int j = 0; j < node->goals.size(); j++) {

                for (auto del : oper->getDelList()) {
                    if (node->goals[j] == del) {
                        consistent = false;
                    }
                }
                for (auto conf : oper->getConflicts()) {
                    if (node->goals[j] == conf) {
                        consistent = false;
                    }
                }
            }
            
            if (operRelevant && consistent) {
                cout<<"considering using "<<oper->getName()<<" to achieve "<<node->goals[i]<<endl;
                vector<string> newgoals = regress(node->goals, oper);
                vector<string> newplan = node->plan;
                newplan.push_back(oper->getName());
                
                string ps = toString(newplan);
                if (visited.find(ps) == visited.end()) {

                    visited[ps] = 1;
                    Node* newNode = new Node;
                    newNode->goals = newgoals;
                    newNode->plan = newplan;
                    q.push(newNode);
                }
            }
        }
        }
        
    }
}


int main(int argc, char * argv[])
{
    
    //OperatorGenerator opersGenerator(argv[1]);
    OperatorReader opersReader(argv[1]);
    vector<Operator*> opers = opersReader.getOperators();
    
    KbReader initReader(argv[2]);
    vector<string> kb = initReader.getFacts();

     while (true) {
         char input[100];
         cin.getline(input,sizeof(input));
         if (input[0] == 'q') {
             exit(0);
         }else {
             vector<string> goals;
             char * pch;
             pch = strtok (input," ");
             while (pch != NULL)
             {
                 cout << "goal: "<<pch<<endl;
                 goals.push_back(pch);
                 pch = strtok (NULL, " ");
             }
             cout<<"initiating goal regression..."<<endl;
             vector<string> plan = goalRegression(goals, opers, kb);

         }
     }
    
    return 0;
}
