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
                    cout << var<<" | at row "<<varRow<<" vertex "<< 5*varRow+j<<" : "<<variables[5*varRow+j]<<" has value "<<value<<endl;
                    return false;
                }
            
        
    }
    
    
    //Englishman in red house
    if (var == "red" && value != assignment.find("Englishman")->second) {
        return false;
    }
    //Spaniard own dog
    if (var == "dog" && value != assignment.find("Spaniard")->second) {
        return false;
    }
    //Norwegian in first house on the left
    if (var == "Norwegian" && value != "1") {
        return false;
    }
    std::string::size_type sz;   // alias of size_t
    int this_house_num = stoi (value,&sz);
    cout <<"this house number: "<<this_house_num<<endl;
    //Green house is right of ivory house
    if (var == "green" ) {
        int i_house_num = stoi (assignment.find("ivory")->second,&sz);
        cout << "ivory house number"<<i_house_num;
        if (this_house_num != i_house_num + 1) {
            return false;
        }
    }
    //Hershey bars lives next to fox

    if (var == "Hershey") {
        int fox_house_num = stoi (assignment.find("fox")->second,&sz);
        cout << "fox house number"<<fox_house_num;

        if (this_house_num != fox_house_num + 1 && this_house_num != fox_house_num - 1) {
            return false;
        }
    }
    //Kit kats in yellow house
    if (var == "Kits Kats" && value != assignment.find("yellow")->second) {
        return false;
    }
    //Norwegian next to blue house
    if (var == "blue" ) {
        int Norwegian_house_num = stoi (assignment.find("Norwegian")->second,&sz);
        cout << "norwegian house number"<<Norwegian_house_num;

        if (this_house_num != Norwegian_house_num + 1 && this_house_num != Norwegian_house_num - 1) {
            return false;
        }
    }
    //Smarties own snails
    if (var == "Smarties" && value != assignment.find("snails")->second) {
        return false;
    }
    //Snickers drink orange juice
    if (var == "orange juice" && value != assignment.find("Snickers")->second) {
        return false;
    }
    //Ukranian drink tea
    if (var == "tea" && value != assignment.find("Ukranian")->second) {
        return false;
    }
    //Japanese eat Milky Ways
    if (var == "Milky Ways" && value != assignment.find("Japanese")->second) {
        return false;
    }
    //Kit Kat next to horse
    if (var == "Kits Kats" ) {
        int horse_house_num = stoi (assignment.find("horse")->second,&sz);
        if (this_house_num != horse_house_num + 1 && this_house_num != horse_house_num - 1) {
            return false;
        }
    }
    //Coffee in green house
    if (var == "coffee" && value != assignment.find("green")->second) {
        return false;
    }
    //Milk in middle house
    if (var == "milk" && value != "3") {
        return false;
    }
    return true;
}