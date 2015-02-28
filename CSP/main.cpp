//
//  main.cpp
//  PathFinding
//
//  Created by Uriana on 1/25/15.
//  Copyright (c) 2015 You Wu. All rights reserved.
//

#include <iostream>
#include <queue>
#include <stack>

#include "ProblemJobs.h"
#define JOB_NUMBER 2

using namespace std;

string selectUnassignedVariable(vector<string> variables, jobMap assignment)
{
    for (int i = 0; i < variables.size(); i++) {
        if (assignment.count(variables[i]) < JOB_NUMBER) {
            return variables[i];
        }
    }
    return "null";
}

jobMap recursiveBackTracking(jobMap assignment, ProblemJobs* csp)
{
    if (assignment.size() == JOB_NUMBER * csp->getVariables().size()) {
        return assignment;
    }
    cout << assignment.size()<<" | ";

    string var = selectUnassignedVariable(csp->getVariables(), assignment);
    cout << var<<endl;
    vector<string> domains = csp->getDomainValues(var);
    for (int i = 0; i < domains.size(); i++) {
        if (csp->consistency(var, domains[i], assignment)) {
            cout << var<<" and "<<domains[i]<<"is consistent"<<endl;
            //add this pair
            assignment.insert(make_pair(var, domains[i]));
            jobMap result = recursiveBackTracking(assignment, csp);
            
            if (result.size() != 0) {
                return result;
            }
            assignment.erase(var);
        }
    }
    jobMap fail;
    return fail;
}

jobMap backTrackingSearch(ProblemJobs* csp)
{
    jobMap init;
    return recursiveBackTracking(init,csp);
}

int main(int argc, char * argv[])
{
    ProblemJobs* p1 = new ProblemJobs();
    jobMap result = backTrackingSearch(p1);
    cout<<"=========\nPuzzle result:"<<endl;
    for (auto it: result) {
        cout << it.first <<" | "<< it.second<<endl;

    }
    
    return 0;
}
