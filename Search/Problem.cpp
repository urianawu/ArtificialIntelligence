//
//  Problem.cpp
//  Search
//
//  Created by Uriana on 2/5/15.
//  Copyright (c) 2015 You Wu. All rights reserved.
//

#include "Problem.h"
Problem::Problem(int nOfStack, int nOfBlock, int randomness)
{
    nBlock = nOfBlock;
    nStack = nOfStack;
    
    char letters[] ="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    //init goal state node
    vector<stack<char>> goalState;
    //string goalHashString = "";
    
    stack<char> firstStack;
    for (int i = 0; i < nBlock; i++) {
        firstStack.push(letters[i]);
        //goalHashString+=letters[i];
    }
    //goalHashString+="#";
    goalState.push_back(firstStack);

    for (int i = 1; i < nStack; i++) {
        stack<char> restStack;
        goalState.push_back(restStack);
        //goalHashString+="#";
    }
    Node* tmp = new Node(goalState);
    
    srand ((unsigned int)time(NULL));
    //get random successors through n iterations
    for (int i = 0; i < randomness; i++) {
        int size = (int)tmp->successors().size();
        tmp = tmp->successors().at(rand()%size);
    }
    init = new Node(tmp->state);
}

Problem::Problem(char* filename)
{
    
    FILE * file;
    file = fopen (filename,"r");
    
    if (file == NULL) {
        perror ("Error opening file");
    }else{
        vector<stack<char>> state;

        //string hashString = "";
        char nOfStack[80];
        fgets(nOfStack, 80, file);
        
        char nOfBlock[80];
        fgets(nOfBlock, 80, file);
        
        nStack = getN(nOfStack);
        nBlock = getN(nOfBlock);

        //read in state block info
        for (int i = 0; i < nStack; i++) {
            int id;
            char blocks[80];
            stack<char> thisStack;
            
            fscanf(file,"%i",&id);
            cout << id <<" | ";
            //read blocks
            fgets(blocks, 80, file);
            char* block = strtok (blocks," ");
            while (block != NULL)
            {
                thisStack.push(block[0]);
                //hashString+=block[0];
                cout << block[0]<<" ";
                block = strtok (NULL, " ");
            }
            state.push_back(thisStack);
            //hashString+="#";
            cout << endl;
            
        }
        init = new Node(state);
    }

}


int Problem::getN(char* line){
    char* str = strtok (line," :");
    str = strtok (NULL, " :");
    
    stringstream stream(str);
    int number = 0;
    stream >> number;
    
    return number;
}