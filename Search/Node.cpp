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
    parent = NULL;
    depth = 0;
    h1 = 0;
    h2 = 0;
    this->state = state;
}

Node::Node(vector<stack<char>> state, Node *p)
{
    parent = p;
    depth = p->depth + 1;
    this->state = state;
    setHeur();
}

void Node::setHeur()
{
    string s = toString();
    int nStack = (int)count(s.begin(), s.end(), '#');
    int nBlock = (int)s.length() - nStack;
    
    char letters[] ="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    //h1
    h1 = nBlock;
    int found = s.find_first_of("#");
    for (int i = 0; i < found; i++) {
        if (s[i] = letters[i]) {
            h1--;
        }
    }
    //h2
    h2 = nBlock;
    
   }
string Node::toString()
{
    string hashString = "";
    vector<stack<char>> tmp = state;
    for (int i = 0; i < tmp.size(); i++) {
        string subString = "";
        while (!tmp.at(i).empty()) {
            string s(1, tmp.at(i).top());
            subString.insert(0, s);
            tmp.at(i).pop();

        }
        hashString+=subString+"#";
    }
    return hashString;
}

void Node::print()
{
    vector<stack<char>> tmp = state;
    for (int i = 0; i < tmp.size(); i++) {
        cout << i+1 << " |";
        string subString = "";
        while (!tmp.at(i).empty()) {
            string s(1, tmp.at(i).top());
            subString.insert(0, " "+s);
            tmp.at(i).pop();
        }
        cout << subString<<endl;
    }
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