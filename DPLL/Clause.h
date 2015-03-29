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
    int index;
    struct parents {
        Clause* p1 = NULL;
        Clause* p2 = NULL;
    }p;

    //Clause();
    Clause(string);
    vector<string> getSymbols();
    string getString();
    string toPrint();
    
    vector<string> resolvable(Clause* cls);
    Clause* resolve(Clause* cls, string p);

    bool operator ==(const Clause& c);
    void operator=(const Clause &c );

private:
    vector<string> symbols;
    string str;
    
    static int NumOfClauses;
    
};
class ResPair{
public:
    ResPair(Clause* i, Clause* j, string p);

    Clause* i;
    Clause* j;
    string p;
};


//class ResPair{
//public:
//    ResPair(int i, int j, string p);
//    
//    int i;
//    int j;
//    string p;
//};

#endif /* defined(__PropLogicProver__Clause__) */
