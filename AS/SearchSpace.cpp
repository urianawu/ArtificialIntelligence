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
    float a, b;
    while(infile >> str >> a >> b) {
        cout << str << " | " <<a<<" "<<b<<endl;
    }
}
