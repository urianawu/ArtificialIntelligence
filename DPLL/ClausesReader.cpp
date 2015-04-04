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
    vector<string> items, actionItems, Acts;
    items = {"Fa","Fx", "Ch", "Gr"};
    actionItems = {"No", "Fx", "Ch", "Gr"};
    //items = {"Fa", "Fx", "Ch"};
    //actionItems = {"No", "Fx", "Ch"};
    int TIME_STEP = 7;
    
    for (int t = 0; t <= TIME_STEP; t++) {
        //location constraints
        for (string i: items) {
            string los_L = getLos(t, i, true);
            string los_R = getLos(t, i, false);
            vector<string> negate_syms = {"-"+los_L,"-"+los_R};
            vector<string> syms = {los_L,los_R};
            
            Clause* cls = new Clause(syms);
            Clause* negate_cls = new Clause(negate_syms);
            clauses.push_back(cls);
            clauses.push_back(negate_cls);
            
        }
    }
    
    //fox eat chicken, chicken eat grain
    for (int t = 0; t <= TIME_STEP; t++) {
            for (bool b : { false, true }) {
                vector<vector<string> > syms;
                //syms.push_back( {getLos(t, "Fx", !b), getLos(t, "Fa", b), getLos(t, "Ch", !b)} );
                //syms.push_back( {getLos(t, "Ch", !b), getLos(t, "Fa", b), getLos(t, "Gr", !b)} );
                
                //syms.push_back( {getLos(t, "Fa", b), getLos(t, "Ch", b), getLos(t, "Gr", b)} );
                //syms.push_back( {getLos(t, "Fa", b), "-"+getLos(t, "Ch", !b), "-"+getLos(t, "Gr", !b)} );
                
                for (vector<string> sym : syms) {
                    Clause* cls = new Clause(sym);
                    clauses.push_back(cls);
                }
            }
        
    }
    
    //action constraints
    for (int t = 0; t < TIME_STEP; t++) {
        vector<string> syms;
        for (string i: actionItems) {
            string act_LR = getAct(t, i, true);
            Acts.push_back(act_LR);
            syms.push_back(act_LR);
            
            string act_RL = getAct(t, i, false);
            Acts.push_back(act_RL);
            syms.push_back(act_RL);
            
        }
        Clause* cls = new Clause(syms);
        clauses.push_back(cls);
    }
    
    for (int t = 0; t < TIME_STEP; t++) {
        for (int i = 0; i < 2*items.size(); i++) {
            for (int j = 1; j < 2*items.size(); j++) {
                if (i < j) {
                    vector<string> syms = {"-"+Acts[TIME_STEP*t+i], "-"+Acts[TIME_STEP*t+j]};
                    Clause* cls = new Clause(syms);
                    clauses.push_back(cls);
                }
            }
        }
    }
    
    for (int t = 0; t < TIME_STEP; t++) {
        for (string it : actionItems) {
            for (bool b : { false, true }) {
                vector<vector<string> > syms;
                if (it.compare("No") != 0) {
                    syms.push_back( {"-"+getAct(t, it, b), getLos(t, it, b)} );
                    syms.push_back( {"-"+getAct(t, it, b), getLos(t+1, it, !b)} );
                }
                
                syms.push_back( {"-"+getAct(t, it, b), getLos(t, "Fa", b)} );
                syms.push_back( {"-"+getAct(t, it, b), getLos(t+1, "Fa", !b)} );
                //no change states
                for (string n_it: items) {
                    if (n_it != it && n_it != "Fa") {
                        syms.push_back({"-"+getAct(t, it, b), "-"+getLos(t, n_it, b), getLos(t+1, n_it, b)});
                        syms.push_back({"-"+getAct(t, it, b), "-"+getLos(t, n_it, !b), getLos(t+1, n_it, !b)});
                    }
                }
                
                for (vector<string> sym : syms) {
                    Clause* cls = new Clause(sym);
                    clauses.push_back(cls);
                }
            }
        }
    }
    
    
    //init
    vector<Clause*> initcls;
    initcls.push_back( new Clause(getLos(0, "Fa", true)) );
    initcls.push_back( new Clause(getLos(0, "Fx", true)) );
    initcls.push_back( new Clause(getLos(0, "Ch", true)) );
    initcls.push_back( new Clause(getLos(0, "Gr", true)) );

    for (auto cls: initcls) {
        clauses.push_back(cls);
    }
    //goal
    vector<Clause*> goalcls;
    goalcls.push_back( new Clause(getLos(TIME_STEP, "Fa", false)) );
    goalcls.push_back( new Clause(getLos(TIME_STEP, "Fx", false)) );
    goalcls.push_back( new Clause(getLos(TIME_STEP, "Ch", false)) );
    goalcls.push_back( new Clause(getLos(TIME_STEP, "Gr", false)) );
    
    for (auto cls: goalcls) {
        clauses.push_back(cls);
    }

}

string ClausesReader::getLos(int time, string item, bool L)
{
    string str;
    if (L) {
        str = "T" + to_string(time) + "_" + item + "L";
    }else {
        str = "T" + to_string(time) + "_" + item + "R";
    }
    return str;
}

string ClausesReader::getAct(int time, string item, bool LR)
{
    string str;
    if (LR) {
        str = "T" + to_string(time) +"_mv_"+item +"_LR";
    }else {
        str = "T" + to_string(time) +"_mv_"+item +"_RL";
    }
    return str;
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
