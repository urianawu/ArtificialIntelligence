//
//  OperatorReader.cpp
//  GoalRegression
//
//  Created by Uriana on 5/6/15.
//  Copyright (c) 2015 You Wu. All rights reserved.
//

#include "OperatorReader.h"
OperatorReader::OperatorReader(char* filename)
{
    ifstream infile(filename);
    string oper;
    while (getline(infile, oper)) {
        istringstream iss(oper);
        string word;
        char type = ' ';
        while(iss >> word) {
            if (type != ' ') {
                switch (type) {
                    case 'O':
                    {
                        Operator* oper = new Operator(word);
                        opers.push_back(oper);
                        break;
                    }
                    case 'p':
                        opers.back()->add2Precond(word);
                        break;
                    case 'a':
                        opers.back()->add2AddList(word);
                        break;
                    case 'd':
                        opers.back()->add2DelList(word);
                        break;
                    case 'c':
                        opers.back()->add2Conflict(word);
                        break;

                    default:
                        break;
                }
            }else {
                if (word == "OPER") {
                    type = 'O';
                }else if (word == "precond:") {
                    type = 'p';
                }else if (word == "addList:") {
                    type = 'a';
                }else if (word == "delList:") {
                    type = 'd';
                }else if (word == "conflict:") {
                    type = 'c';
                }else if (word == "END") {
                    type = 'E';
                }
            }
            
        }
    }
    infile.close();
    
}