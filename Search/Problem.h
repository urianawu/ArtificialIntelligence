//
//  Problem.h
//  Search
//
//  Created by Uriana on 2/5/15.
//  Copyright (c) 2015 You Wu. All rights reserved.
//

#ifndef __Search__Problem__
#define __Search__Problem__

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>

#include "Node.h"

using namespace std;

class Problem{
public:
    int nStack, nBlock;
    Node* init;
    string goalString;
    
    Problem(int nOfStack, int nOfBlock, int randomness); // random generator
    Problem(char * filename); //problem from file
    
private:
    vector<stack<char>> setGoalState();
    int getN(char* line);
};
#endif /* defined(__Search__Problem__) */
