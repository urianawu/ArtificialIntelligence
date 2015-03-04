//
//  ProblemJobs.h
//  Search
//
//  Created by Uriana on 2/5/15.
//  Copyright (c) 2015 You Wu. All rights reserved.
//

#ifndef __AS__ProblemJobs__
#define __AS__ProblemJobs__

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>

using namespace std;
typedef multimap<string, string> Map;

class ProblemJobs{
public:
    ProblemJobs();
    vector<string> getVariables();
    vector<string> getDomainValues(string var);
    bool consistency(string var, string value, Map assignment);
    
protected:
    vector<string> variables;
    vector<string> domainValues;

};
#endif /* defined(__Search__ProblemJobs__) */
