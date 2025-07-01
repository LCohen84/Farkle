#include "Player.h"
#include <string>

// Player Constructors
Player::Player()
{
	this->score = 0;
}

Player::Player(std::string name)
{
	this->name = name;
	this->score = 0;
}

Player::~Player()
{

}

// Definitions for functions 
void Player::setScore(int score) 
{ 
	this->score = score; 
}

// Adding score to the current score
void Player::addToScore(int score) 
{ 
	this->score += score; 
}

// Displaying user score
int Player::getScore() 
{ 
	return this->score; 
}

// Setting the user name
void Player::setName(std::string name) 
{ 
	this->name = name; 
}

// Returning user name
std::string Player::getName() const 
{ 
	return this->name; 
}