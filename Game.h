#pragma once

#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include <vector>
#include <fstream>

class Game {
private:
    std::vector<Player> players;
    static const int numDicePerPlayer = 6;

public:
    Game(); // Constructor
    // Main game loop
    void play(std::vector<Player>& currentPlayers, std::ofstream& scoreFile); 
    // Method for the initial phase of the game
    void initialPhase(std::vector<Player>& players, std::ofstream& scoreFile);
};

#endif // GAME_H