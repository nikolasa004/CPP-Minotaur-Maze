#include "Shield.h"
#include <iostream>

void Shield::gotMessage()
{
	std::cout<<R"(______________________________
|                            |
| @@@@@@@@@@@@@@@@@@@@@@@@@@ |
| @                        @ |
| @           /\           @ |
| @         {    }         @ |
| @          |  |          @ |
| @          |  |          @ |
| @   ^ -----|  |----- ^   @ |
| @ <                    > @ |
| @   \/-----|  |-----\/   @ |
| @          |  |          @ |
| @          |  |          @ |
| @          |  |          @ |
| @          |  |          @ |
| @          |  |          @ |
| @         {    }         @ |
| @           \/           @ |
 \ @                      @ /
  \ @                    @ /
   \ @                  @ /
    \ @                @ /
     \ @              @ /
      \ @            @ /
       \ @@@@@@@@@@@@ /
        ---------------)"<<std::endl;
	std::cout << "You have activated the Shield effect! You are now invulnerable to the Minotaur!" << std::endl;
}

void Shield::currentMessage()
{
	if (turnsValid == 2)
	{
		std::cout << "The Shield is still active, you have it for two more turns!" << std::endl;
	}
	else if (turnsValid == 1)
	{
		std::cout << "What is this maze, they are leaving items forever, but when you get them, they disappear in a second! You have the Shield for one more turn!" << std::endl;
	}
	else
	{
		std::cout << "The Shield is active for " << turnsValid << " more turns!" << std::endl;
	}
}

void Shield::lostMessage()
{
	std::cout << "The Shield has disappeared! You are now vulnerable to the Minotaur again!" << std::endl;
}