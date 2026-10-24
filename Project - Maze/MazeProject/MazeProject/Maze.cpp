#include "Maze.h"
#include "FogOfWarEffect.h"
#include "Sword.h"
#include "Shield.h"
#include "Hammer.h"
#include <iostream>

void Maze::printMaze()
{
	if (itemEffects["Fog of War"] != nullptr)
	{
		ItemEffect* effect = itemEffects["Fog of War"];
		int playerX = playerPosition.first;
		int playerY = playerPosition.second;

		char fog;
		if (effect->getTurnsValid() == 2)
		{
			fog = '#';
		}
		else if (effect->getTurnsValid() == 1)
		{
			fog = 'X';
		}
		else
		{
			fog = '+';
		}

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1)
				{
					std::cout<<maze[i][j]<<" ";
				}
				else if (i >= playerY - 1 && i <= playerY + 1 && j >= playerX - 1 && j <= playerX + 1)
				{
					std::cout << maze[i][j]<<" ";
				}
				else
				{
					std::cout << fog<<" ";
				}
			}
			std::cout << std::endl;
		}
	}
	else
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				std::cout << maze[i][j]<<" ";
			}
			std::cout << std::endl;
		}
	}
}

void Maze::printPathFromEntranceToExit()
{
	for(int i = 0; i < pathFromEntranceToExit.size(); i++)
	{
		std::pair<int, int> position = pathFromEntranceToExit[i];
		maze[position.second][position.first] = 'O';
	}

	printMaze();
}

void Maze::win()
{
	std::cout<<R"(                                  _____
                                 |     |
                                 | | | |
                                 |_____|
                           ____ ___|_|___ ____
                          ()___)         ()___)
                          // /|           |\ \\
                         // / |           | \ \\
                        (___) |___________| (___)
                        (___)   (_______)   (___)
                        (___)     (___)     (___)
                        (___)      |_|      (___)
                        (___)  ___/___\___   | |
                         | |  |           |  | |
                         | |  |___________| /___\
                        /___\  |||     ||| //   \\
                       //   \\ |||     ||| \\   //
                       \\   // |||     |||  \\ //
                        \\ // ()__)   (__()
                              ///       \\\
                             ///         \\\
                           _///___     ___\\\_
                          |_______|   |_______|)"<<std::endl;

	std::cout << "Congratulations! You have escaped the maze!" << std::endl;
	if (enemyPosition.first != 0)
	{
		std::cout << "But wait a minute, wasn't whole point of this to kill the minotaur?! Ahh whatever, hope next guy will." << std::endl;
	}
	else
	{
		std::cout<<"You have killed the minotaur! You are the hero of the day!"<<std::endl;
	}
	std::cout<<R"( /$$     /$$ /$$$$$$  /$$   /$$       /$$      /$$  /$$$$$$  /$$   /$$
|  $$   /$$//$$__  $$| $$  | $$      | $$  /$ | $$ /$$__  $$| $$$ | $$
 \  $$ /$$/| $$  \ $$| $$  | $$      | $$ /$$$| $$| $$  \ $$| $$$$| $$
  \  $$$$/ | $$  | $$| $$  | $$      | $$/$$ $$ $$| $$  | $$| $$ $$ $$
   \  $$/  | $$  | $$| $$  | $$      | $$$$_  $$$$| $$  | $$| $$  $$$$
    | $$   | $$  | $$| $$  | $$      | $$$/ \  $$$| $$  | $$| $$\  $$$
    | $$   |  $$$$$$/|  $$$$$$/      | $$/   \  $$|  $$$$$$/| $$ \  $$
    |__/    \______/  \______/       |__/     \__/ \______/ |__/  \__/)"<<std::endl;

	delete itemEffects["Fog of War"];
	itemEffects["Fog of War"] = nullptr;
	printMaze();

	scoreRecorder.setGameWon();
}

void Maze::lose()
{
	std::cout<<R"(       -""\
    .-"  .`)     (
   j   .'_+     :[                )      .^--..
  i    -"       |l                ].    /      i
 ," .:j         `8o  _,,+.,.--,   d|   `:::;    b
 i  :'|          "88p;.  (-."_"-.oP        \.   :
 ; .  (            >,%%%   f),):8"          \:'  i
i  :: j          ,;%%%:; ; ; i:%%%.,        i.   `.
i  `: ( ____  ,-::::::' ::j  [:```          [8:   )
<  ..``'::::8888oooooo.  :(jj(,;,,,         [8::  <
`. ``:.      oo.8888888888:;%%%8o.::.+888+o.:`:'  |
 `.   `        `o`88888888b`%%%%%88< Y888P""'-    ;
   "`---`.       Y`888888888;;.,"888b."""..::::'-'
          "-....  b`8888888:::::.`8888._::-"
             `:::. `:::::O:::::::.`%%'|
              `.      "``::::::''    .'
                `.                   <
                  +:         `:   -';
                   `:         : .::/
                    ;+_  :::. :..;;;
                    ;;;;,;;;;;;;;,;;)"<<std::endl;
	std::cout<<R"( /$$     /$$ /$$$$$$  /$$   /$$       /$$        /$$$$$$   /$$$$$$  /$$$$$$$$
|  $$   /$$//$$__  $$| $$  | $$      | $$       /$$__  $$ /$$__  $$|__  $$__/
 \  $$ /$$/| $$  \ $$| $$  | $$      | $$      | $$  \ $$| $$  \__/   | $$   
  \  $$$$/ | $$  | $$| $$  | $$      | $$      | $$  | $$|  $$$$$$    | $$   
   \  $$/  | $$  | $$| $$  | $$      | $$      | $$  | $$ \____  $$   | $$   
    | $$   | $$  | $$| $$  | $$      | $$      | $$  | $$ /$$  \ $$   | $$   
    | $$   |  $$$$$$/|  $$$$$$/      | $$$$$$$$|  $$$$$$/|  $$$$$$/   | $$   
    |__/    \______/  \______/       |________/ \______/  \______/    |__/)"<<std::endl;
	std::cout << "You have been eaten! I just hope next guy will be better." << std::endl;

	delete itemEffects["Fog of War"];
	itemEffects["Fog of War"] = nullptr;
	printMaze();
}

std::vector<std::pair<int, int>> Maze::getPossibleEnemyMoves()
{
	int enemyX = enemyPosition.first;
	int enemyY = enemyPosition.second;
	std::vector<std::pair<int, int>> possibleMoves;

	if(hardMode)
	{
		if (playerPosition.first < enemyX && maze[enemyY][enemyX - 1] != '#' && maze[enemyY][enemyX - 1] != 'U' && maze[enemyY][enemyX - 1] != 'I')
		{
			possibleMoves.push_back(std::make_pair(enemyX - 1, enemyY));
		}
		if (playerPosition.first > enemyX && maze[enemyY][enemyX + 1] != '#' && maze[enemyY][enemyX + 1] != 'U' && maze[enemyY][enemyX + 1] != 'I')
		{
			possibleMoves.push_back(std::make_pair(enemyX + 1, enemyY));
		}
		if (playerPosition.second < enemyY && maze[enemyY - 1][enemyX] != '#' && maze[enemyY - 1][enemyX] != 'U' && maze[enemyY - 1][enemyX] != 'I')
		{
			possibleMoves.push_back(std::make_pair(enemyX, enemyY - 1));
		}
		if (playerPosition.second > enemyY && maze[enemyY + 1][enemyX] != '#' && maze[enemyY + 1][enemyX] != 'U' && maze[enemyY + 1][enemyX] != 'I')
		{
			possibleMoves.push_back(std::make_pair(enemyX, enemyY + 1));
		}
	
	}
	if (!hardMode || possibleMoves.empty())
	{
		if (maze[enemyY][enemyX - 1] != '#' && maze[enemyY][enemyX - 1] != 'U' && maze[enemyY][enemyX - 1] != 'I')
		{
			possibleMoves.push_back(std::make_pair(enemyX - 1, enemyY));
		}
		if (maze[enemyY][enemyX + 1] != '#' && maze[enemyY][enemyX + 1] != 'U' && maze[enemyY][enemyX + 1] != 'I')
		{
			possibleMoves.push_back(std::make_pair(enemyX + 1, enemyY));
		}
		if (maze[enemyY - 1][enemyX] != '#' && maze[enemyY - 1][enemyX] != 'U' && maze[enemyY - 1][enemyX] != 'I')
		{
			possibleMoves.push_back(std::make_pair(enemyX, enemyY - 1));
		}
		if (maze[enemyY + 1][enemyX] != '#' && maze[enemyY + 1][enemyX] != 'U' && maze[enemyY + 1][enemyX] != 'I')
		{
			possibleMoves.push_back(std::make_pair(enemyX, enemyY + 1));
		}
	}

	return possibleMoves;
}

bool Maze::moveEnemy()
{
	int enemyX = enemyPosition.first;
	int enemyY = enemyPosition.second;

	std::vector<std::pair<int, int>> possibleMoves=getPossibleEnemyMoves();

	for (int i = 0; i < possibleMoves.size(); i++)
	{
		if (possibleMoves[i]==playerPosition)
		{
			if (itemEffects["Shield"] != nullptr)
			{
				std::cout << "Stupid minotaur, he ate your shield! You are safe, for now." << std::endl;
				delete itemEffects["Shield"];
				itemEffects["Shield"] = nullptr;

				scoreRecorder.incrementItemsUsed();

				return false;
			}
			
			//1% chance to avoid the minotaur
			int avoidNumber = rand() % 100;
			if (avoidNumber == 0)
			{
				std::cout<<"Hmm, for some reason minotaur decided to avoid you this time, guess you have a bad breath. Run before he changes his mind!"<<std::endl;
				return false;
			}

			maze[enemyY][enemyX] = '.';
			maze[playerPosition.second][playerPosition.first] = 'M';

			lose();
			return true;
		}
	}

	std::pair<int, int> newEnemyPosition = possibleMoves[rand() % possibleMoves.size()];

	for (int i = 0; i < itemsPositions.size(); i++)
	{
		if (newEnemyPosition == itemsPositions[i])
		{
			std::cout<<"Oh no! The minotaur destroyed the item!"<<std::endl;
			itemsPositions.erase(itemsPositions.begin() + i);
			break;
		}
	}

	maze[enemyY][enemyX] = '.';
	enemyPosition.first = newEnemyPosition.first;
	enemyPosition.second = newEnemyPosition.second;
	maze[enemyPosition.second][enemyPosition.first] = 'M';
	
	return false;
}

void Maze::displayItemsMessages()
{
	for (const std::pair<std::string, ItemEffect*>& mapItem : itemEffects)
	{
		ItemEffect* effect = mapItem.second;
		if (effect != nullptr)
		{
			if (effect->getTurnsValid() == 0)
			{
				effect->lostMessage();
				itemEffects[effect->getName()] = nullptr;
				delete effect;
			}
			else
			{
				effect->currentMessage();
				effect->addTurns(-1);
			}
		}
	}
}

void Maze::addEffect()
{
	int itemIndex = rand() % itemNames.size();
	std::string itemName = itemNames[itemIndex];

	std::string sword = "Sword";
	std::string shield = "Shield";
	std::string hammer = "Hammer";

	int combinedTurns = 0;
	if (itemEffects[sword] != nullptr)
	{
		combinedTurns += itemEffects[sword]->getTurnsValid();
	}
	if (itemEffects[shield] != nullptr)
	{
		combinedTurns += itemEffects[shield]->getTurnsValid();
	}
	if (itemEffects[hammer] != nullptr)
	{
		combinedTurns += itemEffects[hammer]->getTurnsValid();
	}

	if (itemEffects[itemName] != nullptr)
	{
		if (itemName == "Fog of War")
		{
			itemEffects[itemName]->addTurns(3);

			scoreRecorder.incrementItemsUsed();
		}
		else
		{	
			//cant have more than two items combined
			if (combinedTurns<=3)
			{
				itemEffects[itemName]->addTurns(3);
				if (itemName == sword)
				{
					std::cout << "Double wielding swords?! Now you must kill the minotaur!" << std::endl;
				}
				else if (itemName == shield)
				{
					std::cout << "Two shileds?! What are you, a turtle?! You can use one as a sled if nothing else!" << std::endl;
				}
				else if (itemName == hammer)
				{
					std::cout << "You have double hammers! I feel sorry for your neighbors!" << std::endl;
				}
			}
			else
			{
				std::cout << "Ufff, kinda hoping for a third hand now, huh? You are already holding two items, you can't have have everything in the world!"<<std::endl;
			}
		}
	}
	else
	{
		if (itemName == "Fog of War")
		{
			itemEffects[itemName] = new FogOfWarEffect();
			itemEffects[itemName]->gotMessage();
		}
		else if (combinedTurns <= 3)
		{
			if (itemName == "Sword")
			{
				itemEffects[itemName] = new Sword();
			}
			else if (itemName == "Shield")
			{
				itemEffects[itemName] = new Shield();
			}
			else if (itemName == "Hammer")
			{
				itemEffects[itemName] = new Hammer();
			}
			itemEffects[itemName]->gotMessage();
		}
		else
		{
			std::cout << "Ufff, kinda hoping for a third hand now, huh? You are already holding two items, you can't have have everything in the world!" << std::endl;
		}
	}
}

bool Maze::movePlayer(char direction)
{
	int newPlayerX = playerPosition.first;
	int newPlayerY = playerPosition.second;

	switch (direction)
	{
		case 'w':
			newPlayerY--;
			break;
		case 'a':
			newPlayerX--;
			break;
		case 's':
			newPlayerY++;
			break;
		case 'd':
			newPlayerX++;
			break;
		default:
			std::cout << "Invalid move" << std::endl;
			return false;
	}

	int numberOfEnemyTurns = 1;
	bool gameEnded = false;

	if (newPlayerX < 0 || newPlayerX >= cols || newPlayerY < 0 || newPlayerY >= rows)
	{
		maze[playerPosition.second][playerPosition.first] = '.';
		if (enemyPosition.first != 0)
		{
			std::cout << "Huh, you actually escaped the maze without using the exit! I guess that's one way to do it. You won." << std::endl;
			std::cout << "But wait a minute, MINOTAUR escaped as well! Guess you won't try to cheat next time!" << std::endl;
			maze[enemyPosition.second][enemyPosition.first] = '.';
			lose();
		}
		else
		{
			std::cout<<"Huh, you actually escaped the maze without using the exit! I guess that's one way to do it."<<std::endl;
			std::cout<<"But who cares, you killed the minotaur! You won!"<<std::endl;
			win();
		}

		return true;
	}

	std::pair<int,int> newPlayerPosition = std::make_pair(newPlayerX,newPlayerY);
	if (maze[newPlayerY][newPlayerX] == '.')
	{
		maze[playerPosition.second][playerPosition.first] = '.';
		playerPosition.first = newPlayerX;
		playerPosition.second = newPlayerY;
		maze[newPlayerY][newPlayerX] = 'R';
	}
	else if (maze[newPlayerY][newPlayerX] == '#')
	{
		if (itemEffects["Hammer"] == nullptr)
		{
			std::cout << "BAAM! You hit your head on the wall!" << std::endl;
			srand(time(0));
			numberOfEnemyTurns = rand() % 4 + 1;

			std::cout << "You were unconscious for " << numberOfEnemyTurns << " turns" << std::endl;
		}
		else
		{
			std::cout<<"YES!!! You demolished that wall! Just hoping it was a right one!"<<std::endl;
			maze[newPlayerY][newPlayerX] = '.';

			delete itemEffects["Hammer"];
			itemEffects["Hammer"] = nullptr;

			scoreRecorder.incrementItemsUsed();
		}
	}
	else if (newPlayerPosition==entrance)
	{
		std::cout << "Yikes! It seems that doors have closed behind you! Guess you have to be brave and move forward." << std::endl;
	}
	else if (newPlayerPosition == enemyPosition)
	{
		if (itemEffects["Sword"] == nullptr)
		{
			std::cout << "I really thought you were the chosen one, and you do THIS?! HEADBUTT THE MINOTAUR?! Well i just hope next player will be smarter." << std::endl;
			maze[playerPosition.second][playerPosition.first] = '.';
			lose();
			gameEnded = true;
		}
		else
		{
			std::cout << "You have killed the minotaur! That's how you do it! Now escape the maze!" << std::endl;
			maze[enemyPosition.second][enemyPosition.first] = '.';
			enemyPosition.first = 0;
			enemyPosition.second = 0;

			delete itemEffects["Sword"];
			itemEffects["Sword"] = nullptr;

			scoreRecorder.setEnemyKilled();
			scoreRecorder.incrementItemsUsed();
		}
	}
	else if (newPlayerPosition==exit)
	{
		maze[playerPosition.second][playerPosition.first] = '.';

		win();
		gameEnded = true;
	}
	else
	{
		std::cout<<"You found an item!"<<std::endl;
		for (int i = 0; i < itemsPositions.size(); i++)
		{
			if (newPlayerPosition == itemsPositions[i])
			{
				itemsPositions.erase(itemsPositions.begin() + i);
				break;
			}
		}

		addEffect();

		maze[playerPosition.second][playerPosition.first] = '.';
		playerPosition.first = newPlayerX;
		playerPosition.second = newPlayerY;
		maze[newPlayerY][newPlayerX] = 'R';

		scoreRecorder.incrementItemsCollected();
	}

	if (gameEnded)
	{
		return gameEnded;
	}
	
	if (enemyPosition.first != 0)
	{
		for (int i = 0; i < numberOfEnemyTurns; i++)
		{
			gameEnded = moveEnemy();
			if (gameEnded)
			{
				return gameEnded;
			}
		}
	}

	displayItemsMessages();

	scoreRecorder.incrementMoves();

	return gameEnded;
}

std::string Maze::getScore()
{
	return scoreRecorder.getScore();
}

int Maze::getFinalScore()
{
	return scoreRecorder.getFinalScore();
}