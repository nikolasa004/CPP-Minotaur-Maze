#pragma once
#include <vector>
//Nikola Savic, 18.12.2024.

//Abstract class for maze generation, it will be inherited by concrete algorithms
//It contains all the necessary data for maze generation, maze itself and positions of entrance, exit, player, enemy and items
//Contains function for generating a maze
class MazeGenerator
{
protected:
	int rows;
	int cols;
	int numberOfItems;
	std::vector<std::vector<char>> maze;
	std::pair<int, int> entrance;
	std::pair<int, int> exit;
	std::pair<int, int> playerPosition;
	std::pair<int, int> enemyPosition;
	std::vector<std::pair<int, int>> itemsPositions;
	std::vector<std::pair<int, int>> pathFromEntranceToExit;
public:
	int getRows() const {
		return rows;
	}
	int getCols() const {
		return cols;
	}
	int getNumberOfItems() const {
		return numberOfItems;
	}
	std::vector<std::vector<char>> getMaze() const {
		return maze;
	}
	std::pair<int, int> getEntrance() const {
		return entrance;
	}
	std::pair<int, int> getExit() const {
		return exit;
	}
	std::pair<int, int> getPlayerPosition() const {
		return playerPosition;
	}
	std::pair<int, int> getEnemyPosition() const {
		return enemyPosition;
	}
	std::vector<std::pair<int, int>> getItemsPositions() const {
		return itemsPositions;
	}
	std::vector<std::pair<int, int>> getPathFromEntranceToExit() const {
		return pathFromEntranceToExit;
	}

	MazeGenerator(int rows, int cols,int numberOfItems, bool addRooms):rows(rows),cols(cols),numberOfItems(numberOfItems) {}

	//Generates a maze with given number of rows and columns
	virtual void generateMaze(bool addRooms) = 0;

	//functions for adding items,entrance and player, exit, enemy nad rooms to the maze
	void addEntrance();
	void addExit();
	void addRooms(std::vector<std::pair<int, int>>& pathPositions);
	void addEnemyAndPlayer(std::vector<std::pair<int,int>> &pathPositions);
	void addItems(std::vector<std::pair<int,int>> &pathPositions);
	void findPathFromEntranceToExit();
};