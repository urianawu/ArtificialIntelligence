//
//  Graph.h
//  Search
//
//  Created by Uriana on 1/26/15.
//  Copyright (c) 2015 You Wu. All rights reserved.
//
//  can only handle integer coordinates

#ifndef __Search__Graph__
#define __Search__Graph__

#include <stdio.h>
#include <stdlib.h>     /* atof */
#include <iostream>
#include <sstream>
#include <string.h>
#include <vector>

using namespace std;

class Graph
{
public:
    int nOfVertices, nOfEdges;
    int * vertices;
    int * edges;
    
    void read(char * filename);

private:
    int getN(char* line);
};

#endif /* defined(__PathFinding__Graph__) */
