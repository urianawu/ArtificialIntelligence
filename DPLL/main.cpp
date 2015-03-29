//
//  main.cpp
//  PathFinding
//
//  Created by Uriana on 1/25/15.
//  Copyright (c) 2015 You Wu. All rights reserved.
//

#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <algorithm>


#include "ClausesReader.h"

using namespace std;
int Clause::NumOfClauses = 0;

//struct Comparator
//{
//    bool operator()(const ResPair& lhs, const ResPair& rhs)
//    {
//        int min1 = min((int)lhs.i->getSymbols().size(), (int)lhs.j->getSymbols().size());
//        int min2 = min((int)rhs.i->getSymbols().size(), (int)rhs.j->getSymbols().size());
//        if ( min1 > min2) {
//            return true;
//        } else {
//            return false;
//        }
//        
//    }
//};




int main(int argc, char * argv[])
{
    ClausesReader kb("example.data");
    
    return 0;
}
