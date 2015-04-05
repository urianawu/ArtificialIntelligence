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
#include <map>

#include "ClausesReader.h"

using namespace std;
int Clause::NumOfClauses = 0;
vector<string> AllSymbols;
int NumOfSymbols = 0;
int NumOfNodes = 0;
bool UC = true, PS = true;

pair<string,bool> findPureSymbol(vector<Clause*> clauses, mMap model, cMap clauseMap)
{
    pair<string, bool> pureSym (" ", NULL);
    vector<string> allLiterals;

    for (int c = 0; c < clauses.size(); c++) {
        auto it = clauseMap.find(clauses[c]);
        if ( it == clauseMap.end()) {
            //all remaining clauses
            //cout<<"remaining:  "<<clauses[c]->toPrint()<<endl;
            vector<string> thisLiterals = clauses[c]->getLiterals();
            
            for (auto it : thisLiterals) {
                string lit = it;
                if (it[0] == '-') {
                    lit.erase(0,1);
                }
                    if (find(allLiterals.begin(), allLiterals.end(), it) == allLiterals.end()
                        && (model.find(lit) == model.end())) {
                        
                        allLiterals.push_back(it);
                    }
                
            }
        }
    }
    for (auto it : allLiterals) {
        //cout<<it<<endl;

        string lit = it;
        bool negate = false;
        if (lit[0] == '-') {
            lit.erase(0, 1);
            //cout<<lit<<endl;
            negate = true;
        }

        if (!negate) {
            if (find(allLiterals.begin(), allLiterals.end(), "-"+it) == allLiterals.end()) {
                cout<<"true pure symbol?: "<<it<<endl;
                pureSym = {it, true};
                return pureSym;
            }
        }else {
            
            if (find(allLiterals.begin(), allLiterals.end(), lit) == allLiterals.end()) {
                cout<<"false pure symbol?: "<<it<<endl;
                pureSym = {lit, false};
                return pureSym;
            }
        }
        
    }
    return pureSym;
}

pair<string, bool> findUnitClause(vector<Clause*> clauses, mMap model, cMap clauseMap)
{
    pair<string, bool> unit (" ", NULL);
    for (int c = 0; c < clauses.size(); c++) {
        auto it = clauseMap.find(clauses[c]);
        if ( it == clauseMap.end()) {
            int assigned = 0;
            vector<string> lits = clauses[c]->getLiterals();
            string implied;

            for (auto it :  lits) {
                string lit = it;
                bool negate = false;
                if (lit[0] == '-') {
                    lit.erase(0, 1);
                    negate = true;
                }
                if (model.find(lit) != model.end()) {
                    if (!negate && !model.find(lit)->second) {
                        assigned++;
                    } else if (negate && model.find(lit)->second) {
                        assigned++;
                    }
                }else {
                    implied = it;
                }
            }
            if (assigned == lits.size() -1) {
                cout<<"unit_clause on " <<clauses[c]->toPrint();
                string lit = implied;
                bool negate = false;
                if (lit[0] == '-') {
                    lit.erase(0, 1);
                    negate = true;
                }

                if (!negate) {
                    cout<< " implies "<<implied<<"=true"<<endl;
                    unit = {lit, true};
                    return unit;
                }else {
                    cout<< " implies "<<lit<<"=false"<<endl;
                    unit = {lit, false};
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

bool DPLL(vector<Clause*> clauses, vector<string> symbols, mMap model)
{
    NumOfNodes++;
    
    cout<< "model= ";
    printModel(model);
    if (NumOfNodes > 1000) {
        cout<<"failed...";
        exit(0);
    }
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
        cout<<"\ntrue props:"<<endl;
        map<string, bool> sortedModel;
        for (auto it : model) {
            sortedModel.emplace(it.first, it.second);
        }
        for (auto it: sortedModel) {
            if (it.second == true) {
                cout<<it.first<<endl;
            }
        }
        cout<<endl;
        
        return true;
    }
    
    //P, value ← FIND-PURE-SYMBOL(symbols, clauses, model)
    if (PS) {
        
    pair<string,bool> pureSym = findPureSymbol(clauses, model, clauseMap);
        //cout<<"------pure symbol: "<<pureSym.first<<" : "<<pureSym.second<<endl;
    //if P is non-null then return DPLL(clauses, symbols – P, model ∪ {P=value})
    if (pureSym.first != " ") {
        cout<<"Pure Symbol on "<<pureSym.first<<"=";
        if (pureSym.second) {
            cout<<"true"<<endl;
        }else {
            cout<<"false"<<endl;
        }

        vector<string> rest = symbols;

        for (int i=0; i<rest.size(); i++) {
            //cout<<rest.at(i)<<" "<<sym<<endl;
            if (rest.at(i).compare(pureSym.first) == 0) {
                //cout<<"erased "<<i<<" "<<rest.at(i)<<endl;
                rest.erase(rest.begin()+i);
            }
        }
        if (AllSymbols.size() < NumOfSymbols)
            AllSymbols.push_back(pureSym.first);
        for (auto syms: AllSymbols) {
            //cout<<"all symbols: "<<syms<<endl;
        }
        mMap model_P = model;
        model_P.emplace(pureSym);
        
        return DPLL(clauses, rest, model_P);
    }
    }
    if (UC) {
        
    
    //P, value ← FIND-UNIT-CLAUSE(clauses, model)
    pair<string, bool> unitClause = findUnitClause(clauses, model, clauseMap);
    
    //if P is non-null then return DPLL(clauses, symbols – P, model ∪ {P=value})
    if (unitClause.first != " ") {
        vector<string> rest = symbols;
        for (int i=0; i<rest.size(); i++) {
            //cout<<rest.at(i)<<" "<<unitClause.first<<endl;
            if (rest.at(i).compare(unitClause.first) == 0) {
                //cout<<"erased "<<i<<" "<<rest.at(i)<<endl;
                rest.erase(rest.begin()+i);

            }
        }
        if (AllSymbols.size() < NumOfSymbols)
            AllSymbols.push_back(unitClause.first);
        mMap model_P = model;
        model_P.emplace(unitClause);
        return DPLL(clauses, rest, model_P);
    }
    }
    //P ← FIRST(symbols); rest ← REST(symbols)
    string P = symbols.front();
    vector<string> rest = symbols;
    rest.erase(rest.begin());
    
    if (AllSymbols.size() < NumOfSymbols)
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
    ClausesReader* kb;
    int choice;
    cout << "1 for example, 2 for Farmer problem: ";
    cin >> (choice);

    if (choice == 1) {
        kb = new ClausesReader("example.data");
    }else {
        kb = new ClausesReader();
    }
    
    //init log
    cout<<"props:"<<endl;
    for (auto it : kb->getSymbols()) {
        cout<<it<<" ";
    }
    
    cout<<"\n\ninitial clauses:"<<endl;
    for (auto it: kb->getClauses()) {
        cout<<it->index<<": "<<it->toPrint();
        cout<<endl;
    }
    cout<<"---------------"<<endl;

    NumOfSymbols = (int)kb->getSymbols().size();
    cout<<"symbol size:"<<NumOfSymbols<<endl;
    mMap init;
    PS = true;
    UC = true;
    DPLL(kb->getClauses(), kb->getSymbols(), init);
    
    //cout<<"all symbols: "<<AllSymbols.size();
    return 0;
}
