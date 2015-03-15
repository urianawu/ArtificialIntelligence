//
//  Clauses.cpp
//  PropLogicProver
//
//  Created by Uriana on 3/15/15.
//  Copyright (c) 2015 You Wu. All rights reserved.
//

#include "Clauses.h"
Clauses::Clauses(char* filename)
{
    ifstream infile(filename);
    string clause;
    while (infile >> clause) {
        clauses.push_back(clause);
        cout<<clause<<endl;
    }
    
//    //buffer string split
//    string buf; // Have a buffer string
//    stringstream ss(str); // Insert the string into a stream
//    
//    vector<string> tokens; // Create vector to hold our words
//    
//    while (ss >> buf)
//        tokens.push_back(buf);
}