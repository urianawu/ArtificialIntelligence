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
int NumOfSymbols = 0;
int NumOfNodes = 0;

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

pair<char,bool> findPureSymbol(vector<Clause*> clauses, cMap clauseMap)
{
    pair<char, bool> pureSym (' ', NULL);
    vector<string> allLiterals;
    for (int c = 0; c < clauses.size(); c++) {
        auto it = clauseMap.find(clauses[c]);
        if ( it == clauseMap.end()) {
            //all remaining clauses
            //cout<<clauses[c]->index<<": "<<clauses[c]->toPrint()<<endl;
            vector<string> thisLiterals = clauses[c]->getLiterals();
            for (auto it : thisLiterals) {
                if (find(allLiterals.begin(), allLiterals.end(), it) == allLiterals.end()) {
                    allLiterals.push_back(it);
                }
            }
        }
    }
    
    for (auto it : allLiterals) {
        if (it.length() == 1) {
            if (find(allLiterals.begin(), allLiterals.end(), "-"+it) == allLiterals.end()) {
                pureSym = {it.front(), true};
                return pureSym;
            }
        }else {
            
            if (find(allLiterals.begin(), allLiterals.end(), it.substr(1,1)) == allLiterals.end()) {
                pureSym = {it.back(), false};
                return pureSym;
            }
        }
        
    }
    return pureSym;
}

pair<char, bool> findUnitClause(vector<Clause*> clauses, mMap model, cMap clauseMap)
{
    pair<char, bool> unit (' ', NULL);
    for (int c = 0; c < clauses.size(); c++) {
        auto it = clauseMap.find(clauses[c]);
        if ( it == clauseMap.end()) {
            int assigned = 0;
            vector<string> lits = clauses[c]->getLiterals();
            string implied;
            for (auto it :  lits) {
                if (model.find(it.back()) != model.end()) {
                    assigned++;
                }else {
                    implied = it;
                }
            }
            if (assigned == lits.size() -1) {
                cout<<"unit_clause on " <<clauses[c]->toPrint();
                if (implied.length() == 1) {
                    cout<< " implies "<<implied<<"=true"<<endl;
                    unit = {implied.back(), true};
                    return unit;
                }else {
                    cout<< " implies "<<implied.back()<<"=false"<<endl;
                    unit = {implied.back(), false};
                    return unit;
                }
            }
        }
    }
    
    return unit;
}

void printModel (mMap model)
{
    //use symbols order to keep models in the right order
    cout << "{ ";
    for (int index = 0; index < AllSymbols.size(); index++) {
        for (auto it=model.begin(); it != model.end(); it++) {
            
            if (it->first == AllSymbols[index]) {
                cout << "'"<<it->first<<"' : ";
                if (it->second) {
                    cout << "True";
                }else {
                    cout << "False";
                }
                
                if (index != AllSymbols.size() -1) {
                    cout <<", ";
                }
                
            }
        }
        
    }
    cout<< " }"<<endl;
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
    NumOfNodes++;
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
    if (allAssigned && model.size() == NumOfSymbols) {
        cout<<"--------\nNodes Searched: "<<NumOfNodes<<"\nsolution:"<<endl;
        printModel(model);
        cout<<"true props:"<<endl;
        for (auto it: model) {
            if (it.second == true) {
                cout<<it.first<<" ";
            }
        }
        cout<<endl;
        
        return true;
    }
    
    //P, value ← FIND-PURE-SYMBOL(symbols, clauses, model)
    pair<char,bool> pureSym = findPureSymbol(clauses, clauseMap);
    
    //if P is non-null then return DPLL(clauses, symbols – P, model ∪ {P=value})
    if (pureSym.first != ' ') {
        cout<<"Pure Symbol on "<<pureSym.first<<"=";
        if (pureSym.second) {
            cout<<"true"<<endl;
        }else {
            cout<<"false"<<endl;
        }

        vector<char> rest = symbols;
        rest.erase(find(rest.begin(), rest.end(), pureSym.first));
        AllSymbols.push_back(pureSym.first);
        mMap model_P = model;
        model_P.emplace(pureSym);
        
        return DPLL(clauses, rest, model_P);
    }
    
    //P, value ← FIND-UNIT-CLAUSE(clauses, model)
    pair<char, bool> unitClause = findUnitClause(clauses, model, clauseMap);
    
    //if P is non-null then return DPLL(clauses, symbols – P, model ∪ {P=value})
    if (unitClause.first != ' ') {
        vector<char> rest = symbols;
        rest.erase(find(rest.begin(), rest.end(), unitClause.first));
        AllSymbols.push_back(unitClause.first);
        mMap model_P = model;
        model_P.emplace(unitClause);
        return DPLL(clauses, rest, model_P);
    }
    
    //P ← FIRST(symbols); rest ← REST(symbols)
    char P = symbols.front();
    vector<char> rest = symbols;
    rest.erase(rest.begin());
    AllSymbols.push_back(P);
    
    bool satisfiability = false;
    mMap model_Ptrue = model;
    model_Ptrue.emplace(P,true);
    mMap model_Pfalse = model;
    model_Pfalse.emplace(P, false);
    
    cout<<"Trying: "<<P<<endl;
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
    cout<<"props:"<<endl;
    for (auto it : kb.getSymbols()) {
        cout<<it<<" ";
    }
    
    cout<<"\ninitial clauses:"<<endl;
    for (auto it: kb.getClauses()) {
        cout<<it->index<<": "<<it->toPrint();
        cout<<endl;
    }
    cout<<"---------------"<<endl;

    NumOfSymbols = (int)kb.getSymbols().size();
    
    mMap init;
    DPLL(kb.getClauses(), kb.getSymbols(), init);
    return 0;
}
