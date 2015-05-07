//
//  OperatorReader.h
//  GoalRegression
//
//  Created by Uriana on 5/6/15.
//  Copyright (c) 2015 You Wu. All rights reserved.
//

#ifndef __GoalRegression__OperatorReader__
#define __GoalRegression__OperatorReader__

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Operator.h"

using namespace std;
class OperatorReader {
public:
    OperatorReader(char* filename);
    vector<Operator*> getOperators(){return opers;}
private:
    vector<Operator*> opers;
};

#endif /* defined(__GoalRegression__OperatorReader__) */
