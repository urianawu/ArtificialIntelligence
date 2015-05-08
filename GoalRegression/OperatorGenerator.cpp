//
//  OperatorGenerator.cpp
//  GoalRegression
//
//  Created by Uriana on 5/6/15.
//  Copyright (c) 2015 You Wu. All rights reserved.
//

#include "OperatorGenerator.h"
OperatorGenerator::OperatorGenerator(char* filename)
{
    vector<string> blocks = {"a","b","c","d"};
    ofstream operFile (filename);
    if (operFile.is_open())
    {
        for (auto it : blocks) {
            for (auto jt : blocks) {
                if (it != jt) {
                    operFile << "OPER pickup("<<it<<","<<jt<<")\n";
                    operFile << "precond: "<<pickupPrecond(it, jt);
                    operFile << "addList: "<<pickupAddList(it, jt);
                    operFile << "delList: "<<pickupPrecond(it, jt);
                    operFile << "conflict: "<<pickupConflict(it);
                    operFile << "END\n";
                    
                    operFile << "OPER puton("<<it<<","<<jt<<")\n";
                    operFile << "precond: "<<pickupAddList(it, jt);
                    operFile << "addList: "<<pickupPrecond(it, jt);
                    operFile << "delList: "<<pickupAddList(it, jt);
                    operFile << "conflict: "<<putonConflict(it);
                    operFile << "END\n";

                }
            }
            operFile << "OPER pickup("<<it<<",table)\n";
            operFile << "precond: "<<"clear("<<it<<") on("<<it<<",table) gripper_empty()\n";
            operFile << "addList: "<<"holding("<<it<<")\n";
            operFile << "delList: "<<"clear("<<it<<") on("<<it<<",table) gripper_empty()\n";
            operFile << "conflict: "<<pickupConflict(it);
            operFile << "END\n";
            
            operFile << "OPER puton("<<it<<",table)\n";
            operFile << "precond: "<<"holding("<<it<<")\n";
            operFile << "addList: "<<"clear("<<it<<") on("<<it<<",table) gripper_empty()\n";
            operFile << "delList: "<<"holding("<<it<<")\n";
            operFile << "conflict: "<<putonConflict(it);
            operFile << "END\n";
        }

        operFile.close();
    }
}

string OperatorGenerator::pickupPrecond(string x, string y)
{
    return "clear("+x+") on("+x+","+y+") gripper_empty()\n";
}

string OperatorGenerator::pickupAddList(string x, string y)
{
    return "holding("+x+") clear("+y+")\n";
}

string OperatorGenerator::pickupConflict(string x)
{
    vector<string> blocks = {"a","b","c","d"};
    vector<string> conflicts;
    for (auto it : blocks) {
        if (it != x) {
            conflicts.push_back("on("+it+","+x+")");
            conflicts.push_back("on("+x+","+it+")");
            conflicts.push_back("holding("+it+")");
        }
    }
    string conflict;
    for (auto it : conflicts) {
        conflict += it;
        if (it != conflicts.back()) {
            conflict += " ";
        }
    }
    conflict += "\n";
    return conflict;
}
string OperatorGenerator::putonConflict(string x)
{
    vector<string> blocks = {"a","b","c","d"};
    vector<string> conflicts;
    for (auto it : blocks) {
        if (it != x) {
            conflicts.push_back("on("+it+","+x+")");
            
        }
        conflicts.push_back("holding("+it+")");
    }
    
    string conflict;
    for (auto it : conflicts) {
        conflict += it;
        if (it != conflicts.back()) {
            conflict += " ";
        }
    }
    conflict += "\n";
    return conflict;
}
