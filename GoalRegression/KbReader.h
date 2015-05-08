//
//  KbReader.h
//  GoalRegression
//
//  Created by Uriana on 5/6/15.
//  Copyright (c) 2015 You Wu. All rights reserved.
//

#ifndef __GoalRegression__KbReader__
#define __GoalRegression__KbReader__

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;
class KbReader {
public:
    KbReader(char* filename);
    vector<string> getFacts(){return facts;}

private:
    vector<string> facts;
};
#endif /* defined(__GoalRegression__KbReader__) */
