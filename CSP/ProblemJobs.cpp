//
//  ProblemJobs.cpp
//  Search
//
//  Created by Uriana on 2/5/15.
//  Copyright (c) 2015 You Wu. All rights reserved.
//

#include "ProblemJobs.h"
ProblemJobs::ProblemJobs()
{
    variables = {"Roberta", "Thelma", "Steve", "Pete"};
    domainValues = {"chef", "guard", "nurse", "clerk", "police officer", "teacher", "actor", "boxer"};
    
}

vector<string> ProblemJobs::getVariables()
{
    return variables;
}

vector<string> ProblemJobs::getDomainValues(string var)
{
    return domainValues;
}

bool ProblemJobs::consistency(string var, string value, jobMap assignment)
{
    //hold no more than two jobs
    if (assignment.count(var) >=2) {
        return false;
    }
    //two jobs cannot be same
    for (auto it:assignment) {
        if (it.second == value) {
            return false;
        }
    }
    
    bool isMale = true;
    //female name: Roberta, Thelma. Male name: Steve, Pete.
    if (var == "Roberta" || var == "Thelma") {
        isMale = false;
    }
    bool need9thGrade = false;
    //nurse, teacher, police need to have higher education
    if (value == "nurse" || value == "teacher" || value == "police officer") {
        need9thGrade = true;
    }
    //Pete has no education past ninth grade
    if (var == "Pete" && need9thGrade) {
        return false;
    }
    //job of nurse is held by a male
    if (value == "nurse" && !isMale) {
        return false;
    }
    //husband of chef is clerk
    if (value == "clerk" && !isMale) {
        return false;
    }
    //Roberta is not boxer
    //Roberta, chef, and police office, these 3 went golfing together
    if ((value == "boxer" || value == "chef" || value == "police officer") && var == "Roberta") {
        return false;
    }
    if (value == "police officer") {
        string prevVar;
        for (auto it:assignment) {
            if(it.second == "chef")
                prevVar = it.first;
        }
        if (var == prevVar) {
            return false;
        }
    }

    //actor is male
    if (value == "actor" && !isMale) {
        return false;
    }
    
    return true;
}
