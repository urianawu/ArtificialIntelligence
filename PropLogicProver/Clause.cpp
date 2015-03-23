//
//  Clause.cpp
//  PropLogicProver
//
//  Created by Uriana on 3/19/15.
//  Copyright (c) 2015 You Wu. All rights reserved.
//

#include "Clause.h"
Clause::Clause(string str)
{
    //buffer string split
    string buf; // Have a buffer string
    stringstream ss(str); // Insert the string into a stream
    while (ss >> buf)
        symbols.push_back(buf);
    
    this->str = str;
    index = NumOfClauses;
    NumOfClauses++;
    
}

vector<string> Clause::getSymbols()
{
    return symbols;
}

string Clause::getString()
{
    
    return str;
}

string Clause::toPrint()
{
    string str;
    cout<<"(";
    for (auto it: symbols) {
        cout<<it;
        if (it != symbols.at(symbols.size() - 1)) {
            cout<<" v ";
        }
    }
    cout<<")";
    return str;
}

vector<string> Clause::resolvable(Clause* cls)
{
    vector<string> p;
    vector<string> sbls = cls->getSymbols();
    
    for (int i = 0; i < symbols.size(); i++) {
        for (int j = 0; j < sbls.size(); j++) {
            vector<string> tmp1 = symbols;
            vector<string> tmp2 = sbls;
            if (("-"+tmp1[i]).compare(tmp2[j]) == 0) {
                //cout << "same: "<<symbols[i]<<" | "<<sbls[j]<<endl;
                p.push_back(symbols[i]);
            }else if (tmp1[i].compare("-"+tmp2[j]) == 0) {
                //cout << "same: "<<symbols[i]<<" | "<<sbls[j]<<endl;
                p.push_back(sbls[j]);
            }
        }
    }
    
    return p;
}

Clause* Clause::resolve(Clause* cls, string p)
{
    vector<string> sbls = cls->getSymbols();
    vector<string> tmp = symbols;

    auto foundI = find(tmp.begin(), tmp.end(), p);
    auto found_I = find(tmp.begin(), tmp.end(), "-"+p);
    
    auto foundJ = find(sbls.begin(), sbls.end(), p);
    auto found_J = find(sbls.begin(), sbls.end(), "-"+p);

    string str = "";

    if (foundI != tmp.end() && found_J != sbls.end()) {
        //cout<<"+ -: "<<*foundI<<"||"<<*found_J<<endl;
        tmp.erase(foundI);
        sbls.erase(found_J);
    }else if (found_I != tmp.end() && foundJ != sbls.end()) {
        //cout<<"- +: "<<*found_I<<"||"<<*foundJ<<endl;

        tmp.erase(found_I);
        sbls.erase(foundJ);

    }
    
    for (auto it: tmp) {
        str += it + " ";
    }
    for (auto it: sbls) {
        str += it + " ";
    }
    
    if (!str.empty()) {
        str.erase(str.end());
    }
    
    Clause* resolved = new Clause(str);
    resolved->p.p1 = this;
    resolved->p.p2 = cls;
    return resolved;
    
}

bool Clause::operator ==(const Clause& c)
{
    
    if (symbols.size() == c.symbols.size()) {
        set<string> s1(symbols.begin(), symbols.end());
        set<string> s2(c.symbols.begin(), c.symbols.end());
        vector<string> v3;
        set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), back_inserter(v3));
        if (v3.size() == symbols.size()) {
            return true;
        }
    }
    
    return false;
}

void Clause::operator=(const Clause &c )
{
    symbols = c.symbols;
    str = c.str;
    index = c.index;
    p = c.p;
}

ResPair::ResPair(Clause* i, Clause* j, string p) {
    this->i = i;
    this->j = j;
    this->p = p;
}

