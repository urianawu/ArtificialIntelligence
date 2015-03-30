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
#include <iterator>     // std::next


#include "ClausesReader.h"

using namespace std;
int Clause::NumOfClauses = 0;
vector<char> AllSymbols;

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

void printModel (mMap model)
{
    //use symbols order to keep models in the right order
    cout << "{ ";
    for (int index = 0; index < model.size(); index++) {
        for (auto it=model.begin(); it != model.end(); it++) {
            
            if (it->first == AllSymbols[index]) {
                cout << "'"<<it->first<<"' : ";
                if (it->second) {
                    cout << "True";
                }else {
                    cout << "False";
                }
                
                if (index != model.size() -1) {
                    cout <<", ";
                }
                
            }
        }
        
    }cout<< " }"<<endl;
}

cMap checkClauses(vector<Clause*> clauses, mMap model)
{
    cMap cls;
    
    for (auto it : clauses) {
        string isSatisfied = it->satisfied(model);
        if ( isSatisfied == "true") {
            cls[it] = true;
        }else if (isSatisfied == "false") {
            cls[it] = false;
        }
    }
    return cls;

}

bool DPLL(vector<Clause*> clauses, vector<char> symbols, mMap model)
{

    cout<< "model= ";
    printModel(model);

    
    //if every clause in clauses is true in model then return true
    //if some clause in clauses is false in model then return false
    
    cMap clauseMap = checkClauses(clauses, model);
    bool allAssigned = true;
    
    for (int c = 0; c < clauses.size(); c++) {
        auto it = clauseMap.find(clauses[c]);
        if ( it != clauseMap.end()) {
            if (it->second != true) {
                
                cout<<it->first->toPrint()<<" unsatisfied! Backtracking....."<<endl;
                return false;
            }
        }else {
            allAssigned = false;
        }
        
    }
    if (allAssigned) {
        cout<<"--------\nsolution:"<<endl;
        printModel(model);
        return true;
    }
    
    
    //P ← FIRST(symbols); rest ← REST(symbols)
    char P = symbols.front();
    vector<char> rest = symbols;
    rest.erase(rest.begin());
    
    bool satisfiability = false;
    mMap model_Ptrue = model;
    model_Ptrue.emplace(P,true);
    //model_Ptrue[P] = true;
    mMap model_Pfalse = model;
    model_Pfalse.emplace(P, false);
    //model_Pfalse[P] = false;
    if (DPLL(clauses, rest, model_Ptrue) || DPLL(clauses, rest, model_Pfalse)) {
        satisfiability = true;
    }
    
    //exit(0); // char char
    return satisfiability;
}


int main(int argc, char * argv[])
{
    ClausesReader kb("example.data");
    //init log
    cout<<"initial clauses:"<<endl;
    for (auto it: kb.getClauses()) {
        cout<<it->index<<": "<<it->toPrint();
        cout<<endl;
    }
    cout<<"---------------"<<endl;
    AllSymbols = kb.getSymbols();
    for (auto it : kb.getSymbols()) {
        cout<<it<<" | ";
    }
    cout<<endl;
    
    bool succeed = false;
    mMap init;
    DPLL(kb.getClauses(), kb.getSymbols(), init);
    cout<<succeed<<endl;
    return 0;
}
