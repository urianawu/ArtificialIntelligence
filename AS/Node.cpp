//
//  Node.cpp
//  PathFinding
//
//  Created by Uriana on 1/28/15.
//  Copyright (c) 2015 You Wu. All rights reserved.
//

#include "Node.h"


Node::Node(cityMap state)
{
    parent = NULL;
    depth = 0;
    value = distance(state);
    this->state = state;
}

Node::Node(cityMap state, Node *p)
{
    parent = p;
    depth = p->depth + 1;
    this->state = state;
    
}

double Node::distance(cityMap state)
{
    double d = 0;
    for(auto x1 = state.begin(); x1 != state.end(); x1++) {

        cout << x1->first << " to ";
        double lat1 = degreeToRad(x1->second.first);
        double lon1 = degreeToRad(x1->second.second);
        
        
        auto x2 = std::next(x1);
        if (x1 == prev(state.end())) {
            x2 = state.begin();
        }
        cout << x2->first << " is ";
        double lat2 = degreeToRad(x2->second.first);
        double lon2 = degreeToRad(x2->second.second);
        
        
        double dlon = lon2 - lon1;
        double dlat = lat2 - lat1;
        double a = pow((sin(dlat/2.0)), 2.0) + cos(lat1) * cos(lat2) * pow((sin(dlon/2.0)), 2.0);
        double c = 2.0 * atan2( sqrt(a), sqrt(1-a) );
        d += floor(3961 * c * 10.0) / 10.0 ;
        cout << d <<endl;
    }
    
    return d;
}

double Node::degreeToRad(double deg)
{
    //convert latitude and longitude values from degrees to radians
    return deg*3.14159/180.0;
}

/*
 
 void Node::print()
 {
 vector<stack<char> > tmp = state;
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
 */
/*
vector<Node*> Node::successors()
{
    vector<Node*> nodes;
    //loop through each pair of stacks
    for (int i = 0; i < state.size(); i++) {
        for (int j = 0; j < state.size(); j++) {
            if (i != j && !state.at(i).empty()) {
                //pick one block on stack i and put on stack j
                vector<stack<char> > tmp = state;
                tmp.at(j).push(tmp.at(i).top());
                tmp.at(i).pop();
                //set new successor node
                nodes.push_back(new Node(tmp, this));
            }
        }
    }
    
    return nodes;
    
}
*/
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
