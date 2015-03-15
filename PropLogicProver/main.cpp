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
#include <limits>


#include "Board.h"
#define INF 1000

using namespace std;
int minValue(Board board, char p, int alpha, int beta, int depth, int limit);
int maxValue(Board board, char p, int alpha, int beta, int depth, int limit);

Move minimaxMove(Board board, char p, int limit)
{
    cout<<"# making move for "<<p<<"..."<<endl;
    
    vector<Move> legalMoves = board.legalMoves(p);
    vector<int> values;
    char Opponent;
    if (p == 'W') {
        Opponent = 'B';
    }else {
        Opponent = 'W';
    }
    
    for (auto it: legalMoves) {
        int value;
        if (p == board.Player) {
            value = minValue(board.makeMove(p, it.x, it.y), Opponent, -INF, INF, 0, limit);
        }else {
            value = maxValue(board.makeMove(p, it.x, it.y), Opponent, -INF, INF, 0, limit);
        }
        values.push_back(value);
        cout<<"# considering: ("<<it.x<<", "<<it.y<<"), mm="<<value<<endl;
    }

    Move bestMove;
    if (p == board.Player) {
        vector<int>::iterator maxValue = max_element(values.begin(), values.end());
        bestMove = legalMoves.at(distance(values.begin(), maxValue));
    }else {
        vector<int>::iterator minValue = min_element(values.begin(), values.end());
        bestMove = legalMoves.at(distance(values.begin(), minValue));
    }
    return bestMove;
}

int maxValue(Board board, char p, int alpha, int beta, int depth, int limit)
{
    char Opponent;
    if (p == 'W') {
        Opponent = 'B';
    }else {
        Opponent = 'W';
    }
    depth++;

    if (board.legalMoves(p).empty() || depth > limit) {
        return board.utility();
    }

    int value = - INF;
    vector<Move> legalMoves = board.legalMoves(p);
    for (auto it: legalMoves) {
        value = max(value, minValue(board.makeMove(p, it.x, it.y), Opponent, alpha, beta, depth, limit));
        if (value >= beta) {
            return value;
        }
        alpha = max(alpha, value);
    }
    return value;
}

int minValue(Board board, char p, int alpha, int beta, int depth, int limit)
{
    char Opponent;
    if (p == 'W') {
        Opponent = 'B';
    }else {
        Opponent = 'W';
    }
    depth++;

    if (board.legalMoves(p).empty() || depth > limit) {
        return board.utility();
    }

    int value = INF;
    
    vector<Move> legalMoves = board.legalMoves(p);
    for (auto it: legalMoves) {
        value = min(value, maxValue(board.makeMove(p, it.x, it.y), Opponent, alpha, beta, depth, limit));
        if (value <= alpha) {
            return value;
        }
        beta = min(beta, value);
    }
    return value;
}

int main(int argc, char * argv[])
{
    if(argc != 4)
    {
        cout<<"# Wrong format.";
        exit(0);
    }
    
    int size = atoi(argv[1]);
    char player = argv[2][0];
    int depth = atoi(argv[3]);

    cout<<"# Othello "<<size<<" "<<player<<" "<<depth<<endl;
    
    srand (time(NULL));

    Board board(size, player);

    while (true) {
        bool gg = true;
        for (int i = 0; i < size*size; i++) {
            if (board.state[i] == '.')
                gg = false;
        }
        if (gg) {
            cout<<"game over"<<endl;
            exit(0);
        }
        
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
                }else {
                    cout << "# Not a legal move"<<endl;
                }
                break;
            }
            case 'm':
            {
                //move operation
                char* substr;
                substr = strtok (input," ");
                substr = strtok (NULL, " ");
                char P = substr[0];
                if (board.legalMoves(P).empty()) {
                    cout<<"forfeit"<<endl;
                }else {
                Move m = minimaxMove(board, P, depth);
                cout<<"("<<m.x<<","<<m.y<<")"<<endl;
                board = board.makeMove(P, m.x, m.y);
                cout<<"# score = "<<board.computeScore()<<endl;
                board.printState();
                }

                break;
            }
            case 'r':
                //remove all stones
                board.resetState();
                board.printState();
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