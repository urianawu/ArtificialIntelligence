//
//  Board.h
//  Othello
//
//  Created by Uriana on 3/4/15.
//  Copyright (c) 2015 You Wu. All rights reserved.
//

#ifndef __Othello__Board__
#define __Othello__Board__

#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;
class Move{
public:
    int x;
    int y;
    bool operator== (const Move& b)
    {
        if (x == b.x && y == b.y) {
            return true;
        }
        return false;
    }
};

class Board{
public:
    char* state;
    int N;
    char Player;
    Board* parent;
    int NumOfEdge, NumOfCorner;
    
    Board(int N, char Player);
    
    void setState(char * state);
    void initState();
    char* getState();
    void printState();
    void resetState();
    
    int computeScore();
    int utility();

    vector<Move> legalMoves(char P);
    Board makeMove(char P1, int x, int y);
private:
    bool isAdjacent(int x, int y, char p);
};
#endif /* defined(__Othello__Board__) */
