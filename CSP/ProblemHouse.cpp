//
//  ProblemHouse.cpp
//  CSP
//
//  Created by Uriana on 2/28/15.
//  Copyright (c) 2015 You Wu. All rights reserved.
//

#include "ProblemHouse.h"
ProblemHouse::ProblemHouse()
{
    //domains are house number
    domainValues = {"1", "2", "3", "4", "5"};
    variables = {   "Englishman", "Spaniard", "Norwegian", "Ukranian", "Japanese",
                    "red", "ivory", "yellow", "blue", "green",
                    "dog", "zebra", "fox", "snails", "horse",
                    "Hershey", "Kits Kats", "Smarties", "Snickers", "Milky Ways",
                    "tea", "water", "milk", "coffee", "orange juice" };
}

bool ProblemHouse:: consistency(string var, string value, Map assignment)
{
    //hold no more than five property
    int count = 0;
    for (auto it:assignment) {
        if (it.second == value) {
            count++;
        }
    }
    if (count == 5) {
        return false;
    }

    //no two man share a house
    int varPos = (int)(find(variables.begin(), variables.end(), var) - variables.begin());
    int varRow = varPos/5;
        for (int j = 0; j < 5; j++) {
                if (assignment.find(variables[5*varRow+j]) != assignment.end() &&assignment.find(variables[5*varRow+j])->second == value) {
                    //cout << var<<" | at row "<<varRow<<" vertex "<< 5*varRow+j<<" : "<<variables[5*varRow+j]<<" has value "<<value<<endl;
                    return false;
                }
            
        
    }
    
    
    //Englishman in red house
    if(!inSameHouse("Englishman", "red", var, value, assignment))
        return false;
    
    //Spaniard own dog
    if(!inSameHouse("Spaniard", "dog", var, value, assignment))
        return false;

    //Norwegian in first house on the left
    if (var == "Norwegian" && value != "1") {
        return false;
    }
    std::string::size_type sz;   // alias of size_t
    int this_house_num = stoi (value,&sz);
    //cout <<"this house number: "<<this_house_num<<endl;
    //Green house is right of ivory house
    if (var == "green" && assignment.find("ivory") != assignment.end()) {
        int i_house_num = stoi (assignment.find("ivory")->second,&sz);
        //cout << "ivory house number"<<i_house_num;
        if (this_house_num != i_house_num + 1) {
            return false;
        }
    }
    if (var == "ivory" && assignment.find("green") != assignment.end()) {
        int g_house_num = stoi (assignment.find("green")->second,&sz);
        //cout << "green house number"<<g_house_num;
        if (this_house_num != g_house_num - 1) {
            return false;
        }
    }
    
    //Hershey bars lives next to fox
    if (var == "Hershey" && assignment.find("fox") != assignment.end()) {
        int fox_house_num = stoi (assignment.find("fox")->second,&sz);
        //cout << "fox house number"<<fox_house_num;

        if (this_house_num != fox_house_num + 1 && this_house_num != fox_house_num - 1) {
            return false;
        }
    }
    if (var == "fox" && assignment.find("Hershey") != assignment.end()) {
        int hershey_house_num = stoi (assignment.find("Hershey")->second,&sz);
        //cout << "hershey house number"<<hershey_house_num;
        
        if (this_house_num != hershey_house_num + 1 && this_house_num != hershey_house_num - 1) {
            return false;
        }
    }
    
    //Kits kats in yellow house
    if(!inSameHouse("Kits Kats", "yellow", var, value, assignment))
        return false;
    
    //Norwegian next to blue house
    if (var == "blue" && assignment.find("Norwegian") != assignment.end()) {
        int Norwegian_house_num = stoi (assignment.find("Norwegian")->second,&sz);
        //cout << "norwegian house number"<<Norwegian_house_num;

        if (this_house_num != Norwegian_house_num + 1 && this_house_num != Norwegian_house_num - 1) {
            return false;
        }
    }
    if (var == "Norwegian" && assignment.find("blue") != assignment.end()) {
        int blue_house_num = stoi (assignment.find("blue")->second,&sz);
        //cout << "blue house number"<<blue_house_num;
        
        if (this_house_num != blue_house_num + 1 && this_house_num != blue_house_num - 1) {
            return false;
        }
    }
    //Smarties own snails
    if(!inSameHouse("Smarties", "snails", var, value, assignment))
        return false;
    
    //Snickers drink orange juice
    if(!inSameHouse("Snickers", "orange juice", var, value, assignment))
        return false;
    
    //Ukranian drink tea
    if(!inSameHouse("Ukranian", "tea", var, value, assignment))
        return false;
    
    //Japanese eat Milky Ways
    if(!inSameHouse("Japanese", "Milky Ways", var, value, assignment))
        return false;
    
    //Kit Kat next to horse
    if (var == "Kits Kats" && assignment.find("horse") != assignment.end()) {
        int horse_house_num = stoi (assignment.find("horse")->second,&sz);
        if (this_house_num != horse_house_num + 1 && this_house_num != horse_house_num - 1) {
            return false;
        }
    }
    if (var == "horse" && assignment.find("Kits Kats") != assignment.end()) {
        int kit_house_num = stoi (assignment.find("Kits Kats")->second,&sz);
        if (this_house_num != kit_house_num + 1 && this_house_num != kit_house_num - 1) {
            return false;
        }
    }
    //Coffee in green house
    if(!inSameHouse("coffee", "green", var, value, assignment))
        return false;
    
    //Milk in middle house
    if (var == "milk" && value != "3") {
        return false;
    }
    return true;
}

bool ProblemHouse::inSameHouse(string property1, string property2, string var, string value, Map assignment)
{
    if (assignment.find(property1) != assignment.end()) {
        if (var == property2 && value != assignment.find(property1)->second) {
            return false;
        }
    }
    if (assignment.find(property2) != assignment.end()) {
        if (var == property1 && value != assignment.find(property2)->second) {
            return false;
        }
    }
    return true;
}