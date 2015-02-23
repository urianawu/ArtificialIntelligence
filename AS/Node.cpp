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
    value = distance(state);
    this->state = state;
    
}

double Node::distance(cityMap state)
{
    double d = 0;
    for(int x1 = 0; x1 < state.size(); x1++) {

        //cout << state.at(x1).name << " to ";
        double lat1 = degreeToRad(state.at(x1).lat);
        double lon1 = degreeToRad(state.at(x1).lon);
        
        int x2 = x1+1;
        if (x1 == state.size()-1) {
            x2 = 0;
        }
        //cout << state.at(x2).name << " is ";
        double lat2 = degreeToRad(state.at(x2).lat);
        double lon2 = degreeToRad(state.at(x2).lon);
        
        
        double dlon = lon2 - lon1;
        double dlat = lat2 - lat1;
        double a = pow((sin(dlat/2.0)), 2.0) + cos(lat1) * cos(lat2) * pow((sin(dlon/2.0)), 2.0);
        double c = 2.0 * atan2( sqrt(a), sqrt(1-a) );
        d += floor(3961 * c * 10.0) / 10.0 ;
        //cout << d <<endl;
    }
    
    return d;
}

double Node::degreeToRad(double deg)
{
    //convert latitude and longitude values from degrees to radians
    return deg*3.14159/180.0;
}


 
void Node::print()
{
    for (auto it: state) {
        cout << it.name << " | ";
    }
    cout << endl;
}


Node* Node::successor()
{
    cityMap newState = state;
    
        int i =  std::rand() % ( newState.size() );
        int j = ( std::rand() % ( newState.size() - i ) );
        swap(newState.at(i), newState.at(i+j));

    
    for (auto it:newState) {
        //cout << (it).name << " | ";
    }
    //cout<<endl;
    Node* scr = new Node(newState, this);
    return scr;
    
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
