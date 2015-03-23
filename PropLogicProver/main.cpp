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
int Clause::NumOfClauses = 0;

struct Comparator
{
    bool operator()(const ResPair& lhs, const ResPair& rhs)
    {
        int min1 = min((int)lhs.i->getSymbols().size(), (int)lhs.j->getSymbols().size());
        int min2 = min((int)rhs.i->getSymbols().size(), (int)rhs.j->getSymbols().size());
        if ( min1 >= min2) {
            return true;
        } else {
            return false;
        }
        
    }
};

void proofTree(Clause* c, int depth)
{
    cout<<endl;
    for (int i = 0; i < 2*depth; i++) {
        cout<<" ";
    }
    cout << c->index << ": " << c->toPrint();
    if (c->p.p1 != NULL && c->p.p2 != NULL) {
        cout<< " ["<<c->p.p1->index <<","<< c->p.p2->index<<"]";
        proofTree(c->p.p1, ++depth);
        proofTree(c->p.p2, depth);
    }else {
        cout<< " input";
    }
}



string resolution(vector<Clause*> clauses)
{
    //init log
    cout<<"initial clauses:"<<endl;
    for (auto it: clauses) {
        cout<<it->index<<": "<<it->toPrint();
        cout<<endl;
    }
    cout<<"---------------"<<endl;
    

    typedef priority_queue<ResPair, vector<ResPair>, Comparator> candidatesType;
    candidatesType candidates;
    
    for (int i = 0; i < clauses.size(); i++) {
        for (int j = i+1; j < clauses.size(); j++) {
            vector<string> p = clauses[i]->resolvable(clauses[j]);
            while (!p.empty()) {
                ResPair pair(clauses[i], clauses[j], p.front());
                candidates.push(pair);
                p.pop_back();
            }
        }
    }
    
    while (!candidates.empty()) {
        ResPair pair = candidates.top();
        candidates.pop();
        //resolve clauses i, j with p
        Clause* ci = pair.i;
        Clause* cj = pair.j;
        Clause* cm = ci->resolve(cj, pair.p);
        
        cout<<"[Qsize="<<candidates.size()<<"] resolving "<<ci->index<<" and "<<cj->index<<" on "<<pair.p<<": "<<ci->toPrint()<<" and "
            <<cj->toPrint()<<" -> "<<cm->toPrint()<<endl;
        
        cout<<cm->index<<": "<<cm->toPrint()<<endl;
        
        if (cm->getString() == "") {
            cout<<"--------\nSuccess!\nproof trace:";
            proofTree(cm, 0);
            return "";
        }
        
        if (find(clauses.begin(), clauses.end(), cm) == clauses.end()) {
            clauses.push_back(cm);
            for (int k = 0; k < clauses.size() - 1; k++) {
                vector<string> p = cm->resolvable(clauses[k]);
                while (!p.empty()) {
                    ResPair mkpair(cm, clauses[k], p.front());
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
    ClausesReader kb("Sammys.data");
    cout<<resolution(kb.getClauses())<<endl;
    
    return 0;
}
