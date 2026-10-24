#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include "ItemEffect.h"
#include "ScoreRecorder.h"
#include "MazeGenerator.h"
//Nikola Savic, 19.12.2024.

//class that represents the maze
//contains the maze itself, the entrance and exit, the player, enemy and item positions and effects
//additionaly contains the score recorder, mode of the game and the path from entrance to exit
class Maze
{
	int rows;
	int cols;
	int numberOfItems;
	std::vector<std::vector<char>> maze;
	std::pair<int, int> entrance;
	std::pair<int, int> exit;
	std::pair<int, int> playerPosition;
	std::pair<int, int> enemyPosition;
	std::vector<std::pair<int, int>> itemsPositions;
	std::unordered_map<std::string, ItemEffect*> itemEffects;
	std::vector<std::string> itemNames;
	ScoreRecorder scoreRecorder;
	bool hardMode = false;
	std::vector<std::pair<int, int>> pathFromEntranceToExit;
public:
	Maze(const MazeGenerator& algorithm,bool hardMode): rows(algorithm.getRows()), cols(algorithm.getCols()),numberOfItems(algorithm.getNumberOfItems()), maze(algorithm.getMaze()), entrance(algorithm.getEntrance()), exit(algorithm.getExit()), playerPosition(algorithm.getPlayerPosition()), enemyPosition(algorithm.getEnemyPosition()),itemsPositions(algorithm.getItemsPositions()), scoreRecorder(rows,cols,numberOfItems),hardMode(hardMode),pathFromEntranceToExit(algorithm.getPathFromEntranceToExit())
	{
		itemEffects["Fog of War"] = nullptr;
		itemNames.push_back("Fog of War");

		itemEffects["Sword"] = nullptr;
		itemNames.push_back("Sword");

		itemEffects["Shield"] = nullptr;
		itemNames.push_back("Shield");

		itemEffects["Hammer"]=nullptr;
		itemNames.push_back("Hammer");
	}
	~Maze()
	{
		for (std::pair<std::string, ItemEffect*> effect : itemEffects)
		{
			delete effect.second;
		}
	}

	int getRows() const { return rows; }
	int getCols() const { return cols; }
	std::vector<std::vector<char>> getMaze() const{ return maze; }
	
	void printMaze();
	bool movePlayer(char direction);
	std::vector<std::pair<int,int>> getPossibleEnemyMoves();
	bool moveEnemy();
	void win();
	void lose();
	//displays messages for the items, depending on how many turns the effect will last
	void displayItemsMessages();
	//adds the effect of the item to the player
	void addEffect();
	//makes complete record of the score and the parameters of the game
	std::string getScore();
	int getFinalScore();
	void printPathFromEntranceToExit();
};

