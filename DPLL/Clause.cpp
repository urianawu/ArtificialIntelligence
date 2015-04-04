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
        literals.push_back(buf);
    
    this->str = str;
    index = NumOfClauses;
    NumOfClauses++;
    
}
Clause::Clause(vector<string> symbols)
{

    literals = symbols;
    string tmp;
    for (auto it: symbols) {
        tmp += it;
        if (it != symbols.back()) {
            tmp += " ";
        }
    }
    str = tmp;
    index = NumOfClauses;
    NumOfClauses++;
    
}



vector<string> Clause::getLiterals()
{
    return literals;
}

string Clause::getString()
{
    
    return str;
}

string Clause::toPrint()
{
    string str;
    cout<<"(";
    for (auto it: literals) {
        cout<<it;
        if (it != literals.at(literals.size() - 1)) {
            cout<<" v ";
        }
    }
    cout<<")";
    return str;
}

string Clause::satisfied(mMap model)
{
    bool assignedAll = true;
    //cout<<index<<": ";
    for (auto it : literals) {
        string lit = it;
        bool negate = false;
        if (lit[0] == '-') {
            lit.erase(0,1);
            negate = true;
        }

        auto jt = model.find(lit);
        if ( jt != model.end()) {
            if ((!negate && jt->second) || (negate && !jt->second)) {
                //cout<<toPrint()<<" : true"<<endl;
                return "true";
            }
        }else {
            assignedAll = false;
        }
    }
    
    if (assignedAll) {
        bool satisfy = false;
        for (auto it : literals) {
            string lit = it;
            bool negate = false;
            if (lit[0] == '-') {
                lit.erase(0, 1);
                negate = true;
            }

            auto jt = model.find(lit);
            if ((negate && !jt->second) || (!negate && jt->second)) {
                //cout<<toPrint()<<" : false"<<endl;
                satisfy = true;
                
            }
        }
        if (!satisfy) {
            return "false";
        }
    }
    
    //cout<<toPrint()<<" : undefined"<<endl;
    return "undefined";
}


bool Clause::operator ==(const Clause& c)
{
    
    if (literals.size() == c.literals.size()) {
        set<string> s1(literals.begin(), literals.end());
        set<string> s2(c.literals.begin(), c.literals.end());
        vector<string> v3;
        set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), back_inserter(v3));
        if (v3.size() == literals.size()) {
            return true;
        }
    }
    
    return false;
}

void Clause::operator=(const Clause &c )
{
    literals = c.literals;
    str = c.str;
    index = c.index;
}


