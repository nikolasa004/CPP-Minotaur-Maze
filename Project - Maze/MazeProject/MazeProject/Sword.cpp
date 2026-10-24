#include "Sword.h"
#include <iostream>

void Sword::gotMessage()
{
	std::cout << R"(                           ___
                          ( ((
                           ) ))
  .::.                    / /(
 'X .-;-.-.-.-.-.-.-.-.-/| ((::::::::::::::::::::::::::::::::::::::::::::::.._
(X ( ( ( ( ( ( ( ( ( ( ( |  ))   -====================================-      _.>
 `X `-;-`-`-`-`-`-`-`-`-\| ((::::::::::::::::::::::::::::::::::::::::::::::''
  `::'                    \ \(
                           ) ))
                          (_(()" << std::endl;
	std::cout << "You have activated the Sword effect! You can now kill the Minotaur! Maybe you are the chosen one!" << std::endl;
}

void Sword::currentMessage()
{
	if (turnsValid == 2)
	{
		std::cout<<"Hmm, weird sword, it seems like it's disappearing?! You have it for two more turns!"<<std::endl;
	}
	else if (turnsValid == 1)
	{
		std::cout << "The Sword is about to disappear, you have it for one more turn!" << std::endl;
	}
	else
	{
		std::cout << "You have the Sword effect for " << turnsValid << " more turns!" << std::endl;
	}
}

void Sword::lostMessage()
{
	std::cout << "Puff! The Sword disappeared! Lame sword if you ask me, three steps and it's gone!" << std::endl;
}