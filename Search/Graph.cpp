//
//  Graph.cpp
//  PathFinding
//
//  Created by Uriana on 1/26/15.
//  Copyright (c) 2015 You Wu. All rights reserved.
//

#include "Graph.h"

void Graph::read(char* filename)
{
    FILE * graphFile;
    graphFile = fopen (filename,"r");
    
    if (graphFile == NULL) {
        perror ("Error opening file");
    }else{
        
        char a[80];
        fgets(a, 80, graphFile);
        
        // check whether the file starts with vertices or edges
        if (a[0] == 'v' || a[0] == 'V') {
            
            //get vertices number
            nOfVertices = getN(a);
            vertices = new int[nOfVertices * 2];
            for (int i = 0; i < nOfVertices * 2; i++) {
                int tmp;
                //skip ID
                fscanf(graphFile,"%d",&tmp);
                //read coordinates
                fscanf(graphFile,"%d",&vertices[i++]);
                fscanf(graphFile,"%d",&vertices[i]);
                //skip newline character
                fgetc(graphFile);
                
            }
            
            //get edge number
            fgets(a, 80, graphFile);
            nOfEdges = getN(a);
            
            edges = new int[nOfEdges * 2];
            for (int i = 0; i < nOfEdges * 2; i++) {
                int tmp;
                //skip ID
                fscanf(graphFile,"%d",&tmp);
                //read coordinates
                fscanf(graphFile,"%d",&edges[i++]);
                fscanf(graphFile,"%d",&edges[i]);
                //skip newline character
                fgetc(graphFile);
                //cout << edges[i-1] << " | " << edges[i] << endl;
            }

            
        }else
            cout << "graph file format incorrect, first line should give the number of vertices.";
        
        
    }
}

int Graph::getN(char* line){
    char* str = strtok (line," :");
    str = strtok (NULL, " :");
    
    stringstream stream(str);
    int number = 0;
    stream >> number;

    return number;
}