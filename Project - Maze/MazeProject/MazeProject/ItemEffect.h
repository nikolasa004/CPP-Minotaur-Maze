#pragma once
#include <string>
//Nikola Savic, 20.12.2024.

//Base class for all item effects, will be used for polymorphism
//Turns valid is the number of turns the effect will last
class ItemEffect
{
protected:
	std::string name;
	int turnsValid;
public:
		ItemEffect() : turnsValid(3) {}
		void addTurns(int turns) { turnsValid += turns; }
		std::string getName() { return name; }
		int getTurnsValid() { return turnsValid; }

		virtual void gotMessage() = 0;
		virtual void currentMessage() = 0;
		virtual void lostMessage() = 0;
};

