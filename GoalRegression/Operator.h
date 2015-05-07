//
//  Operator.h
//  GoalRegression
//
//  Created by Uriana on 5/6/15.
//  Copyright (c) 2015 You Wu. All rights reserved.
//

#ifndef __GoalRegression__Operator__
#define __GoalRegression__Operator__

#include <stdio.h>
#include <string>
#include <vector>

using namespace std;
class Operator {
public:
    Operator(string name);
    
    void setPrecond(vector<string> preconds);
    void add2Precond(string precond);
    void setAddList(vector<string> addList);
    void add2AddList(string add);
    void setDelList(vector<string> delList);
    void add2DelList(string del);
    void setConflict(vector<string> conflicts);
    void add2Conflict(string conflict);

    string getName(){return name;}
    vector<string> getPrecond(){return preconds;}
    vector<string> getAddList(){return addList;}
    vector<string> getDelList(){return delList;}
    vector<string> getConflicts(){return conflicts;}
    
private:
    string name;
    vector<string> preconds;
    vector<string> addList;
    vector<string> delList;
    vector<string> conflicts;
    
};
#endif /* defined(__GoalRegression__Operator__) */
