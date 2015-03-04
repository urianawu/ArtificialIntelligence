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
    domainValues = {"Roberta", "Thelma", "Steve", "Pete"};
    variables = {"chef", "guard", "nurse", "clerk", "police officer", "teacher", "actor", "boxer"};
    
}

vector<string> ProblemJobs::getVariables()
{
    return variables;
}

vector<string> ProblemJobs::getDomainValues(string var)
{
    return domainValues;
}

bool ProblemJobs::consistency(string var, string value, Map assignment)
{
    //hold no more than two jobs
    int job_count = 0;
    for (auto it:assignment) {
        if (it.second == value) {
            job_count++;
        }
    }
    if (job_count == 2) {
        return false;
    }
    
    bool isMale = true;
    //female name: Roberta, Thelma. Male name: Steve, Pete.
    if (value == "Roberta" || value == "Thelma") {
        isMale = false;
    }
    bool need9thGrade = false;
    //nurse, teacher, police need to have higher education
    if (var == "nurse" || var == "teacher" || var == "police officer") {
        need9thGrade = true;
    }
    //Pete has no education past ninth grade
    if (value == "Pete" && need9thGrade) {
        return false;
    }
    //job of nurse is held by a male
    if (var == "nurse" && !isMale) {
        return false;
    }
    //husband of chef is clerk
    if (var == "clerk" && !isMale) {
        return false;
    }
    //Roberta is not boxer
    //Roberta, chef, and police office, these 3 went golfing together
    if ((var == "boxer" || var == "chef" || var == "police officer") && value == "Roberta") {
        return false;
    }
    // chef is not police officer
    if (var == "police officer" && value == assignment.find("chef")->second) {
        return false;
    }

    //actor is male
    if (var == "actor" && !isMale) {
        return false;
    }
    
    return true;
}
