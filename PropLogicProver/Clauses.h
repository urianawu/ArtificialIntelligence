//
//  Clauses.h
//  PropLogicProver
//
//  Created by Uriana on 3/15/15.
//  Copyright (c) 2015 You Wu. All rights reserved.
//

#ifndef __PropLogicProver__Clauses__
#define __PropLogicProver__Clauses__

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;
class Clauses{
public:
    vector<string> clauses;
    Clauses(char* filename);
    
};
#endif /* defined(__PropLogicProver__Clauses__) */
