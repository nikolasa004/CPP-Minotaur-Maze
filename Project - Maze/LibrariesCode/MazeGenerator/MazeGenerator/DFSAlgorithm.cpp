#include "pch.h"
#include "DFSAlgorithm.h"
#include <stack>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iostream>

void DFSAlgorithm::generateMaze(bool addRoomsToMaze)
{
	std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

	addEntrance();

	std::stack<std::pair<int,int>> stack;
	stack.push(playerPosition);

	std::vector<std::pair<int,int>> pathPositions;

	bool alreadyAdded = false;
	while (!stack.empty())
	{
		std::pair<int,int> current=stack.top();
		stack.pop();

		int x = current.first;
		int y = current.second;

		if (alreadyAdded)
		{
			alreadyAdded = false;
		}
		else
		{
			maze[y][x] = '.';
			if (x != playerPosition.first || y != playerPosition.second)
			{
				pathPositions.push_back(std::make_pair(x, y));
			}
		}

		std::vector < std::pair<int, int >> possibleMoves;
		std::vector<std::pair<int, int>> neighbours;

		//up
		if (y - 2 > 0 && maze[y - 2][x] == '#')
		{
			possibleMoves.push_back(std::make_pair(x, y - 2));
			neighbours.push_back(std::make_pair(x, y - 1));
		}
		//down
		if (y + 2 < rows-1 && maze[y + 2][x] == '#')
		{
			possibleMoves.push_back(std::make_pair(x, y + 2));
			neighbours.push_back(std::make_pair(x, y + 1));
		}
		//left
		if (x - 2 > 0 && maze[y][x - 2] == '#')
		{
			possibleMoves.push_back(std::make_pair(x - 2, y));
			neighbours.push_back(std::make_pair(x - 1, y));
		}
		//right
		if (x + 2 < cols-1 && maze[y][x + 2] == '#')
		{
			possibleMoves.push_back(std::make_pair(x + 2, y));
			neighbours.push_back(std::make_pair(x + 1, y));
		}

		if (possibleMoves.empty())
		{
			alreadyAdded = true;
			continue;
		}

		int index = rand() % possibleMoves.size();
		stack.push(current);
		stack.push(possibleMoves[index]);
		int neighbourX = neighbours[index].first;
		int neighbourY = neighbours[index].second;
		maze[neighbourY][neighbourX] = '.';
		pathPositions.push_back(std::make_pair(neighbourX, neighbourY));
	}

	//algorithm doesnt work nicely with even number of rows or columns so we fix it
	if (rows % 2 == 0)
	{
		int necessaryX=rand()%(cols-2)+1;
		maze[rows-2][necessaryX] = '.';
		for (int i = 1; i < cols-2; i++)
		{
			if (i != necessaryX)
			{
				int random = rand() % 2;
				if (random == 0)
				{
					maze[rows - 2][i] = '.';
					pathPositions.push_back(std::make_pair(i, rows - 2));
				}
			}
		}
	}
	if (cols % 2 == 0)
	{
		for (int i = 1; i < rows - 1; i++)
		{
			int random = rand() % 2;
			if (random == 0)
			{
				maze[i][cols - 2] = '.';
				pathPositions.push_back(std::make_pair(cols - 2, i));
			}
		}
	}

	addExit();

	if (addRoomsToMaze)
	{
		addRooms(pathPositions);
	}

	addEnemyAndPlayer(pathPositions);
	addItems(pathPositions);

	std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

	std::chrono::nanoseconds time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
	double timeInSeconds = time.count() / 1e9;
	std::cout << "Time needed for maze generation: " <<timeInSeconds<< " seconds" << std::endl;

	findPathFromEntranceToExit();
}