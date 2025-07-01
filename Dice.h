#pragma once

#include <cstdlib>
#include <iostream>
#include <vector>

class Dice
{
private:
    // number of dice faces
    static const int faces = 6;

public:
    Dice();
    // Function Declarations
    static int rollDice();
    static std::vector<int> selectDiceToPutAway();
    static bool remainingDice(std::vector<int>& remDice, int& points, const std::vector<int>& putAwayDice);
    static bool checkDice(int diceArray[], int& points);
};



