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
    hn = 0;
    this->state = state;
}

Node::Node(vector<stack<char>> state, Node *p)
{
    parent = p;
    depth = p->depth + 1;
    this->state = state;
}

void Node::calculateHeur(int choice)
{
    string s = toString();
    int found = (int)s.find_first_of("#");

    int nStack = (int)count(s.begin(), s.end(), '#');
    int nBlock = (int)s.length() - nStack;
    string letters ="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";


    //h1
    if (choice == 1) {
        hn = nBlock;
        for (int i = 0; i < found; i++) {
            if (s[i] == letters[i]) {
                hn--;
            }
        }

    }else {
        //h2
        //For each block that has the correct support structure (i.e. " the complete structure underneath it is exactly as it should be), substract one point for every block in the support structure. For each block that has an incorrect support structure, add one point for every block in the existing support structure.
        //define the correct support structure
        //for first stack: bottom char precedes top char in letters string
        //for rest stacks: top char precedes bottom char in letters string
        
        hn = nBlock*(nBlock-1)/2;
        //first stack
        vector<stack<char>> tmp = state;

        string firstString;
        while (!tmp.at(0).empty()) {
            firstString.insert(0, 1, tmp.at(0).top());

            tmp.at(0).pop();
        }
        for (int i = 1; i < firstString.length(); i++) {
            string substr = firstString.substr(0,i+1);
            if ((int)letters.find(substr) == 0) {
                hn -= i;
            }else{
                hn += i;

            }
        }

        //rest stacks
        for (int i = 1; i < nStack; i++) {
            s = s.substr(found+1);
            found = (int)s.find_first_of("#");
            for (int j = 1; j < found; j++) {
                string substr = s.substr(0, j+1);
                reverse(substr.begin(), substr.end());

                if ((int)letters.find(substr) != string::npos) {
                    hn -= j;

                }else{
                    hn += j;

                }
            }
            
        }
    }
                
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

bool Node::isAdjacent(char a, char b)
{
    string letters ="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    string first;
    first.assign(1, a);
    

    string second;
    second.assign(1, b);
    
    string combined = first + second;
    std::size_t found = letters.find(combined);
    if (found!=std::string::npos){
        return true;
    }
    
    return false;
}