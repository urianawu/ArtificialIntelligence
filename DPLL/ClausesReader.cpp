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
    //cout<<"initial clauses:"<<endl;
    while (getline(infile, clause)) {
        Clause* cls = new Clause(clause);
        clauses.push_back(cls);
        //cout<<NumOfClauses<<": ("<<clause<<")"<<endl;
    }
    //cout<<"---------------"<<endl;
    

}

vector<Clause*> ClausesReader::getClauses()
{
    return clauses;
}