//
//  main.cpp
//  PathFinding
//
//  Created by Uriana on 1/25/15.
//  Copyright (c) 2015 You Wu. All rights reserved.
//

#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <algorithm>

#include "Board.h"

using namespace std;
Move minimaxMove(Board board, char p, int limit)
{
    Move tmp;
    return tmp;
}

int minValue(Board board, char p, int depth, int limit)
{
    return 0;
}

int maxValue(Board board, char p, int depth, int limit)
{
    return 0;
}

int main(int argc, char * argv[])
{
    int size = atoi(argv[1]);
    char color = argv[2][0];
    int depth = atoi(argv[3]);
    cout<<"# Othello "<<size<<" "<<color<<" "<<depth<<endl;
    Board board(size, color);

    while (true) {
        //detect user input
        char input[100];
        cin.getline(input,sizeof(input));
        switch (input[0]) {
            case 'i':
                //init operation
                board.initState();
                board.printState();
                break;
            case 'p':
            {
                //put operation
                char* substr;
                substr = strtok (input," ");
                substr = strtok (NULL, " ");
                char P = substr[0];
                substr = strtok (NULL, " ");
                int x = atoi(substr);
                substr = strtok (NULL, " ");
                int y = atoi(substr);
                Move put;
                put.x = x;
                put.y = y;
                vector<Move> moves = board.legalMoves(P);
                if (find(moves.begin(), moves.end(), put)!= moves.end()){
                    board = board.makeMove(P, x, y);
                    board.printState();
                    cout<<"# score = "<<board.computeScore();
                }else {
                    cout << "# Not a legal move"<<endl;
                }
                break;
            }
            case 'm':
                //move operation
                break;
            case 'r':
                //remove all stones
                board.resetState();
                break;
            case 'q':
                //quit program
                exit(0);
                break;
            default:
                cout << "# Invalid Input"<<endl;
                break;
        }

    }
    
    return 0;
}
