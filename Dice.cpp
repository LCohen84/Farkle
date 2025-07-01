#include "Dice.h"
#include <cstdlib>

Dice::Dice()
{
}

// Function for rolling Dice
int Dice::rollDice()
{
	return (rand() % faces) + 1;

}

std::vector<int> Dice::selectDiceToPutAway()
{
	std::vector<int> putAwayDice;

	std::cout << "How many dice do you want to put away?\n";
	int userDice;
	std::cin >> userDice;

	// Ask the user which dice they want to put away
	for (int i = 0; i < userDice; ++i) {
		int dice;
		std::cout << "Enter the number of dice to put away (1-" << faces << "): ";
		std::cin >> dice;

		// Validate user input
		if (dice >= 1 && dice <= faces) {
			putAwayDice.push_back(dice);
		}
		else {
			std::cout << "Invalid input. Please enter a number between 1 and " << faces << "." << std::endl;
			// Decrement loop counter to re-prompt for input
			--i; 
		}
	}

	return putAwayDice;
}

// Function to roll the remainig Dice that was not put away
bool Dice::remainingDice(std::vector<int>& remDice, int& points, const std::vector<int>& putAwayDice)
{
	int diceCounter[6] = { 0 };

	int counter = 0;
	std::cout << "Put Away Dice: ";

	// Display the Dice put away for the user
	for (int i = 0; i < putAwayDice.size(); i++)
	{
		std::cout << putAwayDice[i] << " ";
	}
	std::cout << std::endl;

	// Count the occurrences of each dice face
	for (int i = 0; i < remDice.size(); i++)
	{
		int roll = remDice[i];
		diceCounter[roll - 1] += 1;
	}

	for (int i = 0; i < remDice.size(); i++)
	{
		if (diceCounter[i] > counter)
		{
			counter = diceCounter[i];
		}

		if (diceCounter[i] >= 3)
		{
			if (i == 0)
			{
				points += 1000;
			}

			else
			{
				points += (i + 1) * 100;
			}
		}
		else if (diceCounter[i] == 2)
		{
			if (i == 0)
			{
				points += 200;
			}
			else if (i == 4)
			{
				points += 100;
			}
		}
		else if (diceCounter[i] == 1)
		{
			if (i == 0)
			{
				points += 100;
			}
			else if (diceCounter[i] == 1)
			{
				if (i == 4)
				{
					points += 50;
				}
			}
		}
	}
	// Farkle check 
	if ((counter < 3) && (diceCounter[0] == 0 && diceCounter[4] == 0))
	{
		return true;
	}
	return false;
}

// Checking the main 6 dice rolls for points and determine if farkle
bool Dice::checkDice(int diceArray[], int& points)
{
	int diceCounter[6] = { 0 };
	int counter = 0;
	
	// checking occurences of the face rolls
	for (int i = 0; i < faces; i++)
	{
		int roll = diceArray[i];

		diceCounter[roll - 1] += 1;
	}
	
	// determining the points for the rolls
	for (int i = 0; i < 6; i++)
	{
		if (diceCounter[i] > counter)
		{
			counter = diceCounter[i];
		}

		if (diceCounter[i] >= 3)
		{
			if (i == 0)
			{
				points += 1000;
			}

			else
			{
				points += (i + 1) * 100;
			}
		}
		else if ((diceCounter[i] == 2 && i == 0) || (diceCounter[i] == 2 && i == 4))
		{
			if (i == 0)
			{
				points += 200;
			}
			else if (i == 4)
			{
				points += 100;
			}
		}
		else if (diceCounter[i] == 1)
		{
			if (i == 0)
			{
				points += 100;
			}
			if (i == 4)
			{
				points += 50;
			}
		}
	}

	// farkle check
	if ((counter < 3) && (diceCounter[0] == 0 && diceCounter[4] == 0))
	{
		return true;
	}
	return false;
}