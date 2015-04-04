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
#include <map>
#include <unordered_map>
#include <sstream>
#include <iostream>

using namespace std;
typedef unordered_map<string, bool> mMap;

class Clause{
public:
    int index;

    //Clause();
    Clause(string);
    Clause(vector<string> symbols);
    vector<string> getLiterals();
    string getString();
    string toPrint();

    string satisfied(mMap model);
    bool operator ==(const Clause& c);
    void operator=(const Clause &c );

private:
    vector<string> literals;
    string str;
    
    static int NumOfClauses;
    
};

typedef unordered_map<Clause*, bool> cMap;


#endif /* defined(__PropLogicProver__Clause__) */
