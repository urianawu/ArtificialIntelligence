//
//  SearchSpace.cpp
//  AS
//
//  Created by Uriana on 2/16/15.
//  Copyright (c) 2015 You Wu. All rights reserved.
//

#include "SearchSpace.h"

void SearchSpace::read(char* filename)
{
    ifstream infile(filename);
    string str;
    float pos[2];
    while(infile >> str >> pos[0] >> pos[1]) {
        txCities.emplace(str, make_pair(pos[0], pos[1]));
    }
    
}
