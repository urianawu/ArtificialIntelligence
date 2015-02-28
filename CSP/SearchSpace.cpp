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
        city tmp;
        tmp.name = str;
        tmp.lat = pos[0];
        tmp.lon = pos[1];
        txCities.push_back(tmp);
    }
    
}
