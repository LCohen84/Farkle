// Farkle.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// London Cohen IT-312
// 4/21/2024 
// 7-1 Final Project Farkle 

#include "Dice.h"
#include "Player.h"
#include "Game.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// const variables
const int numDicePerPlyr = 6;


int main()
{
        std::string ascii_art = R"(
    ________________ __________ ____  __.____     ___________
    \_   _____/  _  \\______   \    |/ _|    |    \_   _____/
     |    __)/  /_\  \|       _/      < |    |     |    __)_
     |     \/    |    \    |   \    |  \|    |___  |        \
     \___  /\____|__  /____|_  /____|__ \_______ \/_______  /
         \/         \/       \/        \/       \/        \/ 
    )";

        // Print the ASCII art
        std::cout << ascii_art << std::endl;


    // Welcoming the payers
    cout << "Welcome to Farkle!" << endl;
    cout << "Here are the rules for Farkle" << endl;
    cout << endl;

    // Opening a stream to access the file
    ifstream inputfile;
    inputfile.open("FARKLE_RULES.txt", ios::in);

    // Open stream to hold scores
    ofstream scoreFile;
    scoreFile.open("ScoreList.txt", ios::in | ios::trunc);

    // Checking if file was open
    if (inputfile.is_open())
    {
        string line;
        cout << "File is open " << endl;
        // Looping until the end of file is reach
        while (getline(inputfile, line))
        {

            if (inputfile.eof())
            {
                break;
            }

            cout << line << endl;
        }
        inputfile.close();
    }
    else
    {
        // Let the user know file was not open
        cout << "File was not open!";
    }

    srand(time(nullptr));

    // Obtain the amount of players
    cout << endl << "How many players will be playing?" << endl;
    int players = 0;
    cin >> players;

    vector<Player> currentPlayers;
    vector<Player>* playerptr = &currentPlayers;

    for (int i = 0; i < players; i++)
    {
        cout << "Player " << (i + 1) << endl;
        cout << "Please enter your name: ";
        string name;
        cin >> name;

        currentPlayers.push_back(Player(name));
        scoreFile << "Player " << (i + 1) << " " << name << endl;
    }

    Game game;
    game.play(currentPlayers, scoreFile);

    return 0;  
}

