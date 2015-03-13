//
//  Board.cpp
//  Othello
//
//  Created by Uriana on 3/4/15.
//  Copyright (c) 2015 You Wu. All rights reserved.
//

#include "Board.h"
Board::Board(int N, char Player)
{
    this->N = N;
    this->Player = Player;
    state = new char[N*N];
    resetState();
}

void Board::initState()
{
    *this = makeMove('W', (N-1)/2, (N-1)/2);
    *this = makeMove('B', (N-1)/2 + 1, (N-1)/2);
    *this = makeMove('W', (N-1)/2 + 1, (N-1)/2 + 1);
    *this = makeMove('B', (N-1)/2, (N-1)/2 + 1);
}

char* Board::getState()
{
    return state;
}

void Board::printState()
{
    for (int x = 0; x < N; x++) {
        cout<<"# ";
        for (int y = 0; y < N; y++) {
            cout<<state[x*N+y]<<" ";
        }
        cout<<endl;
    }
}

void Board::resetState()
{
    for (int i = 0; i < N*N; i++) {
        state[i] = '.';
    }
}
int Board::computeScore()
{
    int countOfB = 0;
    int countOfW = 0;
    for (int i = 0; i < N*N; i++) {
        if (state[i] == 'B') {
            countOfB++;
        }else if (state[i] == 'W') {
            countOfW++;
        }
            
    }
    if (Player == 'B') {
        return countOfB - countOfW;
    }else if (Player == 'W') {
        return countOfW - countOfB;
    }
    
    return 0;
}

vector<Move> Board::legalMoves(char P)
{
    vector<Move> moves;
    char Opponent;
    if (P == 'W') {
        Opponent = 'B';
    }else {
        Opponent = 'W';
    }

    for (int x = 0; x < N; x++) {
        for (int y = 0; y < N; y++) {
            if (isAdjacent(x, y, Opponent)) {
                Board testMove = makeMove(P, x, y);
                int testScore = testMove.computeScore();
            
                if (abs(testScore - computeScore()) > 1) {
                    Move legal;
                    legal.x = x;
                    legal.y = y;
                    moves.push_back(legal);
                }
            }
        }
    }
    return moves;
}

Board Board::makeMove(char P, int x, int y)
{
    char * temp = new char[N*N];
    for (int i = 0; i < N*N; i++) {
        temp[i] = state[i];

    }
    temp[x*N+y] = P;
    
    char Opponent;
    if (P == 'W') {
        Opponent = 'B';
    }else {
        Opponent = 'W';
    }
    //flip
    for (int i=0 ; i<N ; i++) {
        for (int j=0 ; j<N ; j++) {
            if (i == x && temp[i*N+j] == P && j != y) {
                    bool allOpponent = true;
                    for (int deltaY = j<y? j+1:j-1; j<y ? deltaY < y: deltaY > y; j<y ?deltaY++: deltaY--) {
                        if (temp[i*N+deltaY] != Opponent) {
                            allOpponent = false;
                        }
                    }
                    if (allOpponent) {
                        for (int deltaY = j<y? j+1:j-1; j<y ? deltaY < y: deltaY > y; j<y ?deltaY++: deltaY--) {
                            temp[i*N+deltaY] = P;
                        }
                    }
                
            }
            if (j == y && temp[i*N+j] == P && i != x) {

                bool allOpponent = true;
                for (int deltaX = i<x?i+1:i-1; i<x ? deltaX < x: deltaX > x; i<x ?deltaX++: deltaX--) {
                    if (temp[deltaX*N+j] != Opponent) {
                        allOpponent = false;
                    }
                }
                if (allOpponent) {
                    for (int deltaX = i<x?i+1:i-1; i<x ? deltaX < x: deltaX > x; i<x ?deltaX++: deltaX--) {
                        temp[deltaX*N+j] = P;
                    }
                }

            }
            if (abs(i-x) == abs(j-y) && temp[i*N+j] == P && i != x) {

                bool allOpponent = true;
                for (int deltaX = i<x?i+1:i-1; i<x ? deltaX < x: deltaX > x; i<x ?deltaX++: deltaX--) {
                    int deltaY = 0;
                    if (i-x == j-y) {
                        deltaY = deltaX+(y-x);
                    }else {
                        deltaY = (x+y) - deltaX;
                    }
                    if (temp[deltaX*N+deltaY] != Opponent) {
                        allOpponent = false;
                    }
                }
                if (allOpponent) {
                    for (int deltaX = i<x?i+1:i-1; i<x ? deltaX < x: deltaX > x; i<x ?deltaX++: deltaX--) {
                        int deltaY = 0;
                        if (i-x == j-y) {
                            deltaY = deltaX+(y-x);
                        }else {
                            deltaY = (x+y) - deltaX;
                        }
                        temp[deltaX*N+deltaY] = P;
                    }
                }
                
            }
        }
    }
    Board newBoard(N, Player);
    newBoard.state = temp;
    return newBoard;

}

bool Board::isAdjacent(int x, int y, char p)
{
    bool adjacent = false;
    if (state[x*N + y] != '.') {
        return adjacent;
    }
    
    for (int deltaY = -1; deltaY <= 1; deltaY++) {
        for (int deltaX = -1; deltaX <= 1; deltaX++) {
            if (x+deltaX >= 0 && x+deltaX < N && y+deltaY >= 0 && y+deltaY < N) {
                if (state[(x+deltaX)*N + (y+deltaY)] == p) {
                    adjacent = true;
                }
            }
        }
    }
    return adjacent;
    

}