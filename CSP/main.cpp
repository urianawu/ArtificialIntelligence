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

int visitedStates = 0;

template <class Problem>
string selectUnassignedVariable(Problem* csp, Map assignment, int MRV)
{
    vector<string> variables = csp->getVariables();
    int maxUnavailableValues = 0;
    int selectedVarIndex = -1;
    if (MRV == 1) {
        //use MRV
        for (int i = 0; i < variables.size(); i++) {
            if (assignment.find(variables[i]) == assignment.end()) {
                int UnavailableValues = 0;
                vector<string> domains = csp->getDomainValues(variables[i]);
                for (int j = 0; j < domains.size(); j++) {
                    if (!csp->consistency(variables[i], domains[j], assignment)) {
                        UnavailableValues++;
                    }
                }
                //update max unavailable values
                if (UnavailableValues > maxUnavailableValues) {
                    maxUnavailableValues = UnavailableValues;
                    cout<<"max unavailable values: "<<maxUnavailableValues<<" at "<<i<<" | ";
                    selectedVarIndex = i;
                }
            }
        }
        return variables[selectedVarIndex];

    }else{
        for (int i = 0; i < variables.size(); i++) {
            if (assignment.find(variables[i]) == assignment.end()) {
                return variables[i];
            }
        }
    }
    return "null";
}

template <class Problem>
Map recursiveBackTracking(Map assignment, Problem* csp, int MRV)
{
    if (assignment.size() == csp->getVariables().size()) {
        return assignment;
    }
    //cout << assignment.size()<<" | ";
    
    string var = selectUnassignedVariable(csp, assignment, MRV);
    cout << "next var : "<<var<<endl;
    vector<string> domains = csp->getDomainValues(var);
    for (int i = 0; i < domains.size(); i++) {
        cout << "domains: "<<domains[i]<<endl;
        visitedStates++;
        if (csp->consistency(var, domains[i], assignment)) {
            cout << var<<" and "<<domains[i]<<" is consistent"<<endl;
            //add this pair
            assignment.insert(make_pair(var, domains[i]));
            Map result = recursiveBackTracking(assignment, csp, MRV);
            
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
Map backTrackingSearch(Problem* csp, int MRV)
{
    Map init;
    return recursiveBackTracking(init,csp, MRV);
}

int main(int argc, char * argv[])
{
    cout<<"Problem 1 or 2 (enter number only): ";
    int choice;
    cin >> choice;
    cin.ignore(100, '\n');
    cout<<"MRV? 1.Yes 2.No :";
    int useMRV;
    cin >> useMRV;
    
    Map result;
    ProblemJobs* p1 = new ProblemJobs();
    ProblemHouse* p2 = new ProblemHouse();
    
    switch (choice) {
        case 1:
            result = backTrackingSearch(p1, useMRV);
            break;
        case 2:
            result = backTrackingSearch(p2, useMRV);
            break;
        default:
            break;
    }
    cout<<"=========\nPuzzle result:"<<endl;
    cout<<"Visited: "<<visitedStates<<" states"<<endl;
    if (result.empty()) {
        cout << "FAIL"<<endl;
        
    }else{
        for (auto it: result) {
            cout << it.first <<" | "<< it.second<<endl;
        }
        
    }
    
    
    return 0;
}
