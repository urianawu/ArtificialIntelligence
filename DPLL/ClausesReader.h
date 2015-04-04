//
//  ClausesReader.h
//  PropLogicProver
//
//  Created by Uriana on 3/15/15.
//  Copyright (c) 2015 You Wu. All rights reserved.
//

#ifndef __PropLogicProver__ClausesReader__
#define __PropLogicProver__ClausesReader__

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "Clause.h"

using namespace std;
class ClausesReader{
public:
    ClausesReader(char* filename);
    ClausesReader();//for FFCG problem
    
    vector<Clause*> getClauses();
    vector<string> getSymbols();
private:
    vector<Clause*> clauses;
    vector<string> symbols;

    string getLos(int time, string item, bool L);
    string getAct(int time, string item, bool LR);
};
#endif /* defined(__PropLogicProver__ClausesReader__) */
