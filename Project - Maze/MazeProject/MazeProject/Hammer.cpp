#include "Hammer.h"
#include <iostream>

void Hammer::gotMessage()
{
	std::cout<<R"(           _
         ./ |
        /  /
      /'  /
     /   /
    /    \
   |      `\
   |        |                                ___________________
   |        |___________________...-------'''- - -  =- - =  - = `.
  /|        |                   \-  =  = -  -= - =  - =-   =  - =|
 ( |        |                    |= -= - = - = - = - =--= = - = =|
  \|        |___________________/- = - -= =_- =_-=_- -=_=-=_=_= -|
   |        |                   ```-------...___________________.'
   |________|
     \    /
     |    |
   ,-'    `-,
   |        |
   `--------')"<<std::endl;
	std::cout << "You have activated the Hammer effect! You can now destroy the wall!" << std::endl;
}

void Hammer::currentMessage()
{
	if (turnsValid == 2)
	{
		std::cout << "The Hammer is still active, you have it for two more turns! Make the hole in the wall, what's the worst that can happen?" << std::endl;
	}
	else if (turnsValid == 1)
	{
		std::cout << "The Hammer is about to disappear, you have it for one more turn! Now is the time to make smart play!" << std::endl;
	}
	else
	{
		std::cout << "The Hammer is active for " << turnsValid << " more turns!" << std::endl;
	}
}

void Hammer::lostMessage()
{
	std::cout << "The Hammer has disappeared! You can't destroy the wall anymore!" << std::endl;
}