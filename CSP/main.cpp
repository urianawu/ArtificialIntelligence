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
#include "ProblemHouse.h"

using namespace std;

string selectUnassignedVariable(vector<string> variables, Map assignment)
{
    for (int i = 0; i < variables.size(); i++) {
        if (assignment.find(variables[i]) == assignment.end()) {
            return variables[i];
        }
    }
    return "null";
}

template <class Problem>
Map recursiveBackTracking(Map assignment, Problem* csp)
{
    if (assignment.size() == csp->getVariables().size()) {
        return assignment;
    }
    //cout << assignment.size()<<" | ";
    
    string var = selectUnassignedVariable(csp->getVariables(), assignment);
    cout << "next var : "<<var<<endl;
    vector<string> domains = csp->getDomainValues(var);
    for (int i = 0; i < domains.size(); i++) {
        cout << "domains: "<<domains[i]<<endl;
        if (csp->consistency(var, domains[i], assignment)) {
            cout << var<<" and "<<domains[i]<<" is consistent"<<endl;
            //add this pair
            assignment.insert(make_pair(var, domains[i]));
            Map result = recursiveBackTracking(assignment, csp);
            
            if (!result.empty()) {
                return result;
            }
            assignment.erase(var);
        }
    }
    Map fail;
    return fail;
}
template <class Problem>
Map backTrackingSearch(Problem* csp)
{
    Map init;
    return recursiveBackTracking(init,csp);
}

int main(int argc, char * argv[])
{
    ProblemJobs* p1 = new ProblemJobs();
    ProblemHouse* p2 = new ProblemHouse();
    Map result = backTrackingSearch(p2);
    cout<<"=========\nPuzzle result:"<<endl;
    if (result.empty()) {
        cout << "FAIL"<<endl;
        
    }else{
        for (auto it: result) {
            cout << it.first <<" | "<< it.second<<endl;
        }
        
    }
    
    
    return 0;
}
