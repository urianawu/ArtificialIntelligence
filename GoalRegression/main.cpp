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

#include "KbReader.h"
#include "OperatorGenerator.h"
#include "OperatorReader.h"

using namespace std;

vector<string> regress(vector<string> goals, vector<Operator*> opers)
{
    

}

void goalRegression(vector<string> goals, vector<Operator*> opers, vector<string> kb)
{
    
}


int main(int argc, char * argv[])
{
    
    //OperatorGenerator opersGenerator(argv[1]);
    OperatorReader opersReader(argv[1]);
    vector<Operator*> opers = opersReader.getOperators();
    
    KbReader initReader(argv[2]);
    vector<string> kb = initReader.getFacts();

     while (true) {
         char input[100];
         cin.getline(input,sizeof(input));
         if (input[0] == 'q') {
             exit(0);
         }else {
             vector<string> goals;
             char * pch;
             pch = strtok (input," ");
             while (pch != NULL)
             {
                 goals.push_back(pch);
                 pch = strtok (NULL, " ");
             }
             
             goalRegression(goals, opers, kb);

         }
     }
    
    return 0;
}
