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

struct ResPair{
    int i;
    int j;
    string p;
};

string resolution(vector<Clause> clauses)
{
    queue<ResPair> candidates;
    for (int i = 0; i < clauses.size(); i++) {
        for (int j = i+1; j < clauses.size(); j++) {
            vector<string> p = clauses[i].resolvable(clauses[j]);
            while (!p.empty()) {
                ResPair pair;
                pair.i = i;
                pair.j = j;
                pair.p = p.front();
                candidates.push(pair);
                p.pop_back();
            }
        }
    }
    
    while (!candidates.empty()) {
        ResPair pair = candidates.front();
        candidates.pop();
        //resolve clauses i, j with p
        Clause ci = clauses[pair.i];
        Clause cj = clauses[pair.j];
        Clause cm = ci.resolve(cj, pair.p);
        if (cm.getString().empty()) {
            return "Success!";
        }
        
        if (find(clauses.begin(), clauses.end(), cm) == clauses.end()) {
            clauses.push_back(cm);
            for (int k = 0; k < clauses.size() - 1; k++) {
                vector<string> p = cm.resolvable(clauses[k]);
                while (!p.empty()) {
                    ResPair mkpair;
                    mkpair.i = (int)clauses.size() - 1;
                    mkpair.j = k;
                    mkpair.p = p.front();
                    candidates.push(mkpair);
                    p.pop_back();
                }

            }
        }
        
        
    }
    
    return "Failure";
}

int main(int argc, char * argv[])
{
    ClausesReader kb("KB.data");
    cout<<resolution(kb.getClauses());
    return 0;
}
