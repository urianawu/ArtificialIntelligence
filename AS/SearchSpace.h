//
//  SearchSpace.h
//  AS
//
//  Created by Uriana on 2/16/15.
//  Copyright (c) 2015 You Wu. All rights reserved.
//

#ifndef __AS__SearchSpace__
#define __AS__SearchSpace__

#include <stdio.h>
#include <stdlib.h>     /* atof */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

using namespace std;
typedef map<string, pair<float, float> > cityMap;

class SearchSpace
{
public:
    cityMap txCities;
    
    void read(char * filename);
    
};


#endif /* defined(__AS__SearchSpace__) */