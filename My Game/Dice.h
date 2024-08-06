#pragma once
#ifndef DICE_H
#define DICE_H 
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <stdexcept>

using std::string;
using std::cout;
using std::endl;

class Dice {
private:
    int sides;
    string weapons[6];

public:
    Dice() : sides(6) {
        
        weapons[0] = "Sword";
        weapons[1] = "Axe";
        weapons[2] = "Bow";
        weapons[3] = "Dagger";
        weapons[4] = "Spear";
        weapons[5] = "Mace";

        
        std::srand(std::time(0));
    }

    std::pair<int, string> roll() {
        int number = std::rand() % sides + 1;
        string weapon = weapons[number - 1];
        return std::make_pair(number, weapon);
    }
};

#endif