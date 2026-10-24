#include "pch.h"
#include "MazeGenerator.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

void MazeGenerator::addEntrance()
{
	srand(time(0));
	maze = std::vector<std::vector<char>>(rows, std::vector<char>(cols, '#'));

	std::vector<int> possibleEntrancesX;
	for (int i = 1; i < cols - 1; i++)
	{
		//does't work well with even number of columns
		if (i % 2 != 0)
		{
			possibleEntrancesX.push_back(i);
		}
	}

	int entranceY = 0;
	int x = rand() % possibleEntrancesX.size();
	int entranceX = possibleEntrancesX[x];

	entrance = std::make_pair(entranceX, entranceY);
	maze[entranceY][entranceX] = 'U';

	playerPosition = std::make_pair(entranceX, entranceY + 1);
}

void MazeGenerator::addExit()
{
	int exitY = rows - 1;
	int sizeScaler = 2;
	//if number of columns is even most right column to the wall doesn't look perfect so the exit can't be there
	if (cols % 2 == 0)
	{
		sizeScaler = 3;
	}
	while (true)
	{
		int exitX = rand() % (cols - sizeScaler) + 1;
		if (maze[exitY - 1][exitX] == '.')
		{
			exit = std::make_pair(exitX, exitY);
			maze[exitY][exitX] = 'I';
			break;
		}
	}
}

void MazeGenerator::addEnemyAndPlayer(std::vector<std::pair<int,int>> &pathPositions)
{
	int randIndex;
	while (true)
	{
		randIndex = rand() % pathPositions.size();
		std::pair<int, int> enemyPos = pathPositions[randIndex];

		//enemy can't be too close to the player
		if ((enemyPos.first > playerPosition.first + 2 || enemyPos.first < playerPosition.first - 2) && (enemyPos.second > playerPosition.second + 2 || enemyPos.second < playerPosition.second - 2))
		{
			enemyPosition = enemyPos;
			maze[enemyPos.second][enemyPos.first] = 'M';

			pathPositions.erase(pathPositions.begin() + randIndex);
			break;
		}
	}

	maze[playerPosition.second][playerPosition.first] = 'R';
}

void MazeGenerator::addItems(std::vector<std::pair<int, int>>& pathPositions)
{
	if (numberOfItems > pathPositions.size())
	{
		std::cout<< "Number of items is greater than number of path tiles, setting number of items to number of tiles" << std::endl;
		numberOfItems=pathPositions.size();
	}

	int randIndex;
	for (int i = 0; i < numberOfItems; i++)
	{
		randIndex = rand() % pathPositions.size();
		std::pair<int, int> itemPos = pathPositions[randIndex];
		itemsPositions.push_back(itemPos);
		maze[itemPos.second][itemPos.first] = 'P';
		pathPositions.erase(pathPositions.begin() + randIndex);
	}
}

void MazeGenerator::addRooms(std::vector<std::pair<int, int>>& pathPositions)
{
	//math for generating number of rooms and their sizes
	int greaterDim;
	if (rows > cols)
	{
		greaterDim = rows;
	}
	else
	{
		greaterDim = cols;
	}

	int minNumberConst = 75+25*greaterDim/15;
	int maxNumberConst = 150+50*greaterDim/15;
	int area = rows * cols;

	int numberOfRooms=rand()%(area/minNumberConst-area/maxNumberConst+1)+area/maxNumberConst;

	int minSizeConst = 4+greaterDim/15;
	int maxSizeConst = greaterDim/2;
	for (int i = 0; i < numberOfRooms; i++)
	{
		int roomWidth = rand() % (cols/minSizeConst-cols/maxSizeConst+1)+cols/maxSizeConst;
		int roomHeight = rand() % (rows/minSizeConst-rows/maxSizeConst+1)+rows/maxSizeConst;

		if (roomHeight < 2)
		{
			roomHeight=2;
		}
		if (roomWidth < 2)
		{
			roomWidth=2;
		}

		int roomX = rand() % (cols-1 - roomWidth) + 1;
		int roomY = rand() % (rows-1 - roomHeight) + 2;

		if (roomX + roomWidth >= cols - 1)
		{
			roomX = cols-1-roomWidth-1;
		}
		if (roomY + roomHeight >= rows - 1)
		{
			roomY = rows-1-roomHeight-1;
		}

		for (int j = roomY; j < roomY + roomHeight; j++)
		{
			for (int k = roomX; k < roomX + roomWidth; k++)
			{
				if (maze[j][k] == '#')
				{
					maze[j][k] = '.';
					pathPositions.push_back(std::make_pair(k, j));
				}
			}
		}
	}
}

void MazeGenerator::findPathFromEntranceToExit()
{
	pathFromEntranceToExit.push_back(playerPosition);
	std::pair<int, int> current = playerPosition;
	std::vector<std::pair<int, int>> intersections;
	std::vector<std::vector<int>> visited(rows, std::vector<int>(cols, 0));
	visited[current.second][current.first] = 1;

	while (current != exit)
	{
		int x = current.first;
		int y = current.second;

		std::vector<std::pair<int, int>> possibleMoves;

		//up
		if (y - 1 > 0 && visited[y - 1][x] == 0 && maze[y-1][x]!='#')
		{
			possibleMoves.push_back(std::make_pair(x, y - 1));
		}
		//down
		if (y + 1 <= rows - 1 && visited[y + 1][x] == 0 && maze[y+1][x]!='#')
		{
			possibleMoves.push_back(std::make_pair(x, y + 1));
		}
		//left
		if (x - 1 > 0 && visited[y][x - 1] == 0 && maze[y][x-1]!='#')
		{
			possibleMoves.push_back(std::make_pair(x - 1, y));
		}
		//right
		if (x + 1 < cols - 1 && visited[y][x + 1] == 0 && maze[y][x+1]!='#')
		{
			possibleMoves.push_back(std::make_pair(x + 1, y));
		}

		if (possibleMoves.empty())
		{
			current = intersections.back();

			while (pathFromEntranceToExit.back() != current)
			{
				pathFromEntranceToExit.pop_back();
			}
			intersections.pop_back();

			continue;
		}

		if (possibleMoves.size() > 1)
		{
			intersections.push_back(current);
		}

		int index = rand() % possibleMoves.size();
		current = possibleMoves[index];
		pathFromEntranceToExit.push_back(current);
		visited[current.second][current.first] = 1;	
	}
}