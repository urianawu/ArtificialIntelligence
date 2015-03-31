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
    
}

vector<Clause*> ClausesReader::getClauses()
{
    return clauses;
}

vector<char> ClausesReader::getSymbols()
{
    for (auto it:clauses) {
        vector<string> literals = it->getLiterals();
        for (int i = 0; i < literals.size(); i++) {
            if (find(symbols.begin(), symbols.end(), literals[i].back()) == symbols.end()) {
                symbols.push_back(literals[i].back());
            }
        }
        
    }
    return symbols;
}
