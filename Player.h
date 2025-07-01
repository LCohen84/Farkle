#pragma once

#include <string>

class Player
{
	private:
		int score;
		std::string name;


	public:
		Player();
		Player(std::string name);
		~Player();

		// Declarations for score setter and getter
		void setScore(int score);
		void addToScore(int score);
		int getScore();
		
		// Declarations for name getter and setter
		void setName(std::string name);
		std::string getName() const;

};
	


