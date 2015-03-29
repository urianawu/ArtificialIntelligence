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
    vector<Clause*> getClauses();
private:
    vector<Clause*> clauses;

};
#endif /* defined(__PropLogicProver__ClausesReader__) */