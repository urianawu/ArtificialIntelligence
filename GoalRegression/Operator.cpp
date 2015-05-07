//
//  Operator.cpp
//  GoalRegression
//
//  Created by Uriana on 5/6/15.
//  Copyright (c) 2015 You Wu. All rights reserved.
//

#include "Operator.h"
Operator::Operator(string name)
{
    this->name = name;
    
}
void Operator::setPrecond(vector<string> preconds)
{
    this->preconds = preconds;
}
void Operator::add2Precond(string precond)
{
    this->preconds.push_back(precond);
}

void Operator::setAddList(vector<string> addList)
{
    this->addList = addList;
}
void Operator::add2AddList(string add)
{
    this->addList.push_back(add);
}
void Operator::setDelList(vector<string> delList)
{
    this->delList = delList;
}
void Operator::add2DelList(string del)
{
    this->delList.push_back(del);
}
void Operator::setConflict(vector<string> conflicts)
{
    this->conflicts = conflicts;
}
void Operator::add2Conflict(string conflict)
{
    this->conflicts.push_back(conflict);
}
