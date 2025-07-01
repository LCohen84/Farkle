#include "Game.h"
#include "Dice.h"
#include <iostream>
#include <string>

using namespace std;

// Constructor
Game::Game() {}

// Method to handle the initial phase of the game
void Game::initialPhase(vector<Player>& currentPlayers, std::ofstream& scoreFile) {
    // Loop for the initial phase of the game
    cout << "Starting the intial phase!" << endl;

    char answer;
    const int numDice = 6;

    cout << endl;
    cout << endl;

    scoreFile << endl << "Inital Round Phase: Players have to hit 1000 to enter the game!" << endl;
    scoreFile << endl;

    for (Player& player : currentPlayers) 
    {
        cout << "------------------------------------------------" << endl;
        cout << "------------------------------------------------" << endl;
        cout << player.getName() << "'s turn First Round" << endl;
        cout << "Score: " << player.getScore() << endl;

        // Continue rolling until the player reaches 1000 points
        while (player.getScore() < 1000) 
        {
            cout << "Are you ready to roll?" << endl;
            cout << "Please enter 'y' or 'n': ";
            cin >> answer;
            answer = tolower(answer);
            cout << endl;

            while (!((answer == 'y') || (answer == 'n'))) 
            {
                cout << "Sorry, that answer is not accepted." << endl;
                cout << "Please type 'y' for yes and 'n' for no:";
                cin.ignore();
                cin >> answer;
            }

            if (answer == 'n') {
                // Player is not ready to roll
                // Skip to the next iteration of the loop
                continue; 
            }

            bool farkle = false;
            int turnPoints = 0;
            int earnPoints = 0;
            int DiceFace[numDice];

            // Continue rolling until a farkle occurs
                // Roll the dice
                for (int i = 0; i < numDice; i++) 
                {
                    DiceFace[i] = Dice::rollDice();
                    cout << "Dice " << (i + 1) << ": " << DiceFace[i] << endl;
                }

                // Check for farkle
                farkle = Dice::checkDice(DiceFace, earnPoints);

                if (farkle) 
                {
                    cout << "You Farkle, all your points are gone for the turn!" << endl;
                }

                // Update turn points and continue rolling
                turnPoints += earnPoints;
                earnPoints = 0;

            // Add turn points to player's score
            player.addToScore(turnPoints);
            scoreFile << player.getName() << ": " << player.getScore() << endl;
            scoreFile << endl;

            
            cout << player.getName() << "'s score is " << player.getScore() << endl;
            cout << endl;
        }
    }

}

// Main game loop
void Game::play(vector<Player>& currentPlayers, std::ofstream& scoreFile)
{
    // Call the initial phase method
    initialPhase(currentPlayers, scoreFile);

    cout << "Main game is beginning!" << endl;
    cout << "Players can now pass turn!" << endl;
    cout << endl;

    int round = 1;
    int winnerScore = 0;
    bool endgame = false;
    string winner = "";
    char answer;
    // Track if a winner has been found
    bool winnerFound = false; 
    // Pointer to the winner player
    Player* winnerPlayer = nullptr; 

    // Looping until someone beats the score
    while (!endgame)
    {
        bool farkle = false;
        int turnPoints = 0;
        int earnPoints = 0;

        int DiceFace[Game::numDicePerPlayer];

        for (Player& player : currentPlayers)
        {
            cout << "------------------------------------------------" << endl;
            cout << "------------------------------------------------" << endl;
            // Askig user are they ready to roll
            cout << player.getName() << "'s turn" << endl;
            cout << "Are you ready to roll?" << endl;
            cout << "Please enter 'y' or 'n': ";
            cin >> answer;
            answer = tolower(answer);
            cout << endl;

            // Making sure input is correct
            while (!((answer == 'y') || (answer == 'n')))
            {
                cout << "Sorry, that answer is not accepted." << endl;
                cout << "Please type 'y' for yes and 'n' for no:";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> answer;

            }
            if (answer == 'y')
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                answer = '0';

                // Rolling six dice
                for (int i = 0; i < Game::numDicePerPlayer; i++)
                {
                    DiceFace[i] = Dice::rollDice();
                    cout << "Dice " << (i + 1) << ": " << DiceFace[i] << endl;
                }

                // Calculate the score and check if they Farkle
                farkle = Dice::checkDice(DiceFace, earnPoints);

                // If farkle, points for the turn are gone and go to the next player
                if (farkle)
                {
                    cout << "You Farkle, all your points are gone for the turn!" << endl;
                    turnPoints = 0;
                    earnPoints = 0;
                    farkle = false;
                    cout << player.getName() << "'s score is " << player.getScore() << endl;
                    continue;
                }

                // Ask the if they want to roll again with some point dice to the side
                else
                {
                    turnPoints = earnPoints;
                    earnPoints = 0;
                    cout << endl << "Your turn points are " << turnPoints << endl;
                    cout << "Do you want to keep point dice and roll your remaining dice?" << endl;
                    cout << "Please type in y or n:" << endl;
                    cin >> answer;
                    answer = std::tolower(answer);

                    while (!((answer == 'y') || (answer == 'n')))
                    {
                        cout << "Sorry, that answer is not accepted." << endl;
                        cout << "Please type 'y' for yes and 'n' for no:";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cin >> answer;
                    }

                    // If the answer is no, the player add the points to score and goes to next player
                    if (answer == 'n')
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        // Adding points to the player score
                        player.addToScore(turnPoints);
                        scoreFile << player.getName() << " Round" << round << " score: " << player.getScore() << endl;
                        scoreFile << endl;
                        cout << player.getName() << "'s score is " << player.getScore() << endl;
                        cout << endl;
                        cout << endl;
                        turnPoints = 0;

                        // Checking is player reach the goal to win
                        if (player.getScore() > 9999)
                        {
                            winner = player.getName(); // Getting the player name that is winning
                            winnerScore = player.getScore();
                            winnerFound = true;
                            endgame = true;
                            // Exit loop if a winner is found
                            break; 
                        }
                        continue;
                    }
                    
                    // PLayer decided to roll again and will put some dice to side then roll the remaining dice
                    else
                    {
                        std::vector<int> putAwayDice;
                        std::vector<int> remainingDice;
                        putAwayDice = Dice::selectDiceToPutAway();
                        std::vector<int> remDice(Game::numDicePerPlayer - putAwayDice.size());
                        cout << "earnpoints equal " << earnPoints << endl;

                        for (int i = 0; i < remDice.size(); i++)
                        {
                            remDice[i] = Dice::rollDice();
                            cout << "Dice " << (i + 1) << ": " << remDice[i] << endl;
                        }

                        // Determining the points of the remaining Dice
                        farkle = Dice::remainingDice(remDice, earnPoints, putAwayDice);

                        if (farkle)
                        {
                            cout << "You Farkle, all your points are gone for the turn!" << endl;
                            earnPoints = 0;
                            turnPoints = 0;
                            farkle = false;
                            cout << player.getName() << "'s score is " << player.getScore() << endl;
                            continue;
                        }

                        // If no farkle the points are added to the player score
                        turnPoints += earnPoints;
                        cout << "Your turn points are " << turnPoints << endl;
                        player.addToScore(turnPoints);
                        scoreFile << player.getName() << " Round" << round << " score: " << player.getScore() << endl;
                        scoreFile << endl;
                        cout << player.getName() << "'s score is " << player.getScore() << endl;
                        turnPoints = 0;
                        cout << endl;
                        cout << endl;

                        // One more check for the winner if they decided to roll the reamining dice
                        if (player.getScore() > 9999)
                        {
                            winner = player.getName();
                            winnerScore = player.getScore();
                            winnerFound = true;
                            endgame = true;
                            // Exit loop if a winner is found
                            break; 
                        }

                        continue;
                    }
                }

            }

        }
        round++;
    }

    if (winnerFound)
    {
        // Announce winner if found
        cout << "The winner as of now is " << winner << endl;
        cout << "Everyone else has one turn to beat them!" << endl;
        cout << endl;
    }


    // Doing one last round for the players who did not reach the score
    // so they can attempt to beat the current winner
    for (Player& player : currentPlayers)
    {
        bool farkle;
        int earnPoints = 0;

        if (!(player.getName() == winner))
        {
            std::cout << player.getName() << "'s turn Last Round" << endl;
            cout << "Are you ready to roll?" << endl;
            cout << "Please enter 'y' or 'n': ";
            cin >> answer;
            answer = tolower(answer);
            cout << endl;

            while (!((answer == 'y') || (answer == 'n')))
            {
                cout << "Sorry, that answer is not accepted." << endl;
                cout << "Please type 'y' for yes and 'n' for no:";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> answer;
            }
            while (answer == 'n')
            { 
                cout << "Are you ready now?" << endl;
                cin >> answer;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

            }
            int diceFace[Game::numDicePerPlayer];

            for (int i = 0; i < (Game::numDicePerPlayer); i++)
            {
                diceFace[i] = Dice::rollDice();
                cout << "Dice " << (i + 1) << ": " << diceFace[i] << endl;
            }

            farkle = Dice::checkDice(diceFace, earnPoints);

            if (farkle)
            {
                cout << "You Farkle, all your points are gone for the turn!" << endl;
                farkle = false;
                earnPoints = 0;
            }

            player.addToScore(earnPoints);
            cout << player.getName() << " has reached " << player.getScore() << " for the last round!" << endl;


            if (&player != winnerPlayer && player.getScore() > winnerScore)
            {
                // Update winner if a player surpasses the winning score
                winnerPlayer = &player;
                winnerScore = player.getScore();
                winner = winnerPlayer->getName();
                break;
            }
        }

    }


        // Announce the new winner if one is found
        cout << "The winner is " << winner << endl;
        cout << "Congratulations!!" << endl;


}