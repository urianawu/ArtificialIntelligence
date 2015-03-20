//
//  Clause.h
//  PropLogicProver
//
//  Created by Uriana on 3/19/15.
//  Copyright (c) 2015 You Wu. All rights reserved.
//

#ifndef __PropLogicProver__Clause__
#define __PropLogicProver__Clause__

#include <stdio.h>
#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <iostream>

using namespace std;

class Clause{
public:
    Clause(string);
    vector<string> getSymbols();
    string getString();
    
    vector<string> resolvable(Clause cls);
    Clause resolve(Clause cls, string p);

    bool operator ==(const Clause& c);

    
private:
    vector<string> symbols;
    string str;
};
#endif /* defined(__PropLogicProver__Clause__) */
