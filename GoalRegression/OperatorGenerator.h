//
//  OperatorGenerator.h
//  GoalRegression
//
//  Created by Uriana on 5/6/15.
//  Copyright (c) 2015 You Wu. All rights reserved.
//

#ifndef __GoalRegression__OperatorGenerator__
#define __GoalRegression__OperatorGenerator__

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
class OperatorGenerator{
public:
    OperatorGenerator(char* filename);
private:
    string pickupPrecond(string x, string y);
    string pickupAddList(string x, string y);
    
    string pickupConflict(string x);
    string putonConflict(string x);

};
#endif /* defined(__GoalRegression__OperatorGenerator__) */
