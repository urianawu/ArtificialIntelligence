//
//  KbReader.cpp
//  GoalRegression
//
//  Created by Uriana on 5/6/15.
//  Copyright (c) 2015 You Wu. All rights reserved.
//

#include "KbReader.h"
KbReader::KbReader(char* filename)
{
    //clear(a)
    ifstream infile(filename);
    string fact;
    while (getline(infile, fact)) {
        if (!fact.empty() && fact[0] != '#') {
            //cout<<fact<<endl;
            facts.push_back(fact);
        }
    }
}