//
//  ClausesReader.cpp
//  PropLogicProver
//
//  Created by Uriana on 3/15/15.
//  Copyright (c) 2015 You Wu. All rights reserved.
//

#include "ClausesReader.h"
ClausesReader::ClausesReader(char* filename)
{
    ifstream infile(filename);
    string clause;
    while (getline(infile, clause)) {
        Clause* cls = new Clause(clause);
        clauses.push_back(cls);
    }
    

}

ClausesReader::ClausesReader()
{
    //vectors of objects
    vector<string> items;
    items = {"Fa","Fx", "Ch", "Gr"};
    
    for (int t = 0; t < 7; t++) {
        for (auto i: items) {
        
            //location constraints
            for (int n = 0; n < 2; n++) {
                string str = "";
                if (n == 1) {
                    str+="-";
                }
                str += "T" + to_string(t) + "_" + i + "L ";
                if (n == 1) {
                    str+="-";
                }
                str+= "T" + to_string(t) + "_" + i + "R";
                Clause* cls = new Clause(str);
                clauses.push_back(cls);
            }
            
            //action constraints
            
        }
    }
    
    
    
}

vector<Clause*> ClausesReader::getClauses()
{
    return clauses;
}

vector<string> ClausesReader::getSymbols()
{
    for (auto it:clauses) {
        vector<string> literals = it->getLiterals();
        for (int i = 0; i < literals.size(); i++) {
            string lit = literals[i];
            if (lit[0] == '-') {
                lit.erase(0,1);
            }
            if (find(symbols.begin(), symbols.end(), lit) == symbols.end()) {
                symbols.push_back(lit);
            }
        }
        
    }
    return symbols;
}
