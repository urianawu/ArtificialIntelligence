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

#include "SearchSpace.h"
#include "Node.h"
#define NUM_OF_ITERATION 1000000

using namespace std;

float schedule(int t)
{
    int highTemp = 31;

    float temp = highTemp - (highTemp/(float)NUM_OF_ITERATION)*t;
    if (temp > 0) {
        return temp;
    }else
        return 0;
}

Node* simulatedAnnealing(cityMap map)
{

    Node* current = new Node(map);
    for (int t = 1; t < NUM_OF_ITERATION; t++) {

        float T = schedule(t);
        if (T == 0 || t == NUM_OF_ITERATION - 1) {
            return current;
        }
        
        Node* next = current->successor();
        float deltaE = next->value - current->value;
        cout<< "iter="<<t<<" len="<<current->value<<" newlen="<<next->value<<" delta="<<deltaE<<" temp="<<T;
        if (deltaE < 0) {
            cout<<endl;
            cout << "updated distance: "<<next->value<<endl;
            current = next;
        }else {
            float randomNum = (float)rand() / RAND_MAX;
            float prob = expf(-deltaE/T);
            cout << " p<"<<prob<<endl;
            if ( randomNum <= prob) {
                current = next;
            }
        }
    }
    return NULL;
    
}

int main(int argc, char * argv[])
{
    SearchSpace* txMap = new SearchSpace;
    char dataFile[80] = "texas-cities.dat";
    txMap->read(dataFile);
    cout << "loading "<<dataFile<<endl;

    srand(time(NULL));
    Node* goal = simulatedAnnealing(txMap->txCities);
    goal->print();
    
    
    return 0;
}
