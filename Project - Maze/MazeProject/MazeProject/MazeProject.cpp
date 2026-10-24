#include <iostream>
#include <string>
#include "Maze.h"
#include "FileManager.h"
#include "Leaderboard.h"
#include "MazeGenerationAlgorithms.h"

//main function that contains the game loop
//takes in command line arguments for the size of the maze and number of items
int main(int argc, char* argv[])
{
	int rows,cols,numberOfItems;

	bool validInput=false;
	try {
		if (argc < 4)
		{
			std::cout<<"Not enough arguments!"<<std::endl;
		}
		else
		{
			rows = std::stoi(argv[1]);
			cols = std::stoi(argv[2]);
			numberOfItems = std::stoi(argv[3]);

			if (rows < 15 || cols < 15)
			{
				std::cout << "Maze size must be at least 15x15" << std::endl;
			}
			else if (numberOfItems < 3)
			{
				std::cout << "Number of items must be at least 3" << std::endl;
			}
			else
			{
				validInput = true;
				std::cout << "Generating " << rows << "x" << cols << " maze" << std::endl;
			}
		}
	}
	catch (const std::invalid_argument& e)
	{
		std::cout<< "Invalid input!"<<std::endl;
	}
	catch (const std::out_of_range& e)
	{
		std::cout<< "Number out of range!"<<std::endl;
	}

	if (!validInput)
	{
		std::cout<<"Defaulting to 21x21 maze"<<std::endl;
		std::cout<<"Using 3 items"<<std::endl;
		rows=21;
		cols=21;
		numberOfItems=3;
	}

	std::cout<<"What mode would you like to play in?"<<std::endl;
	std::cout<<"1. Normal mode(enemy moves randomly)"<<std::endl;
	std::cout<<"2. Hard mode(enemy moves towards player)"<<std::endl;
	int mode;
	std::cin>>mode;

	bool hardMode=false;
	if (mode == 2)
	{
		hardMode=true;
	}
	else if (std::cin.fail())
	{
		std::cout<<"Invalid input, defaulting to normal mode"<<std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	else if (mode != 1)
	{
		std::cout << "Invalid input, defaulting to normal mode" << std::endl;
	}

	std::cout<<"Would you like to add rooms to the maze?"<<std::endl;
	std::cout<<"1. Yes"<<std::endl;
	std::cout<<"2. No"<<std::endl;
	int rooms;
	std::cin>>rooms;

	bool addRooms=true;
	if (rooms == 2)
	{
		addRooms = false;
	}
	else if (std::cin.fail())
	{
		std::cout<<"Invalid input, defaulting to adding rooms"<<std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	else if (rooms != 1)
	{
		std::cout << "Invalid input, defaulting to adding rooms" << std::endl;
	}

    DFSAlgorithm dfs(rows,cols,numberOfItems,addRooms);

	Maze maze(dfs,hardMode);
	FileManager fileManager("../../Results");
	Leaderboard leaderboard("../../Leaderboard");

	std::cout<<"Enter Q to quit"<<std::endl;
	bool gameEnded = false;
	while (true)
	{
		maze.printMaze();

		std::cout<<"Enter move w(up), a(left), s(down), d(right): ";
		char move;
		std::cin>>move;

		if (move == 'Q')
		{
			break;
		}

		gameEnded=maze.movePlayer(move);
		if (gameEnded)
		{
			fileManager.generateFile(maze);
			if (leaderboard.checkScore(maze.getFinalScore()))
			{
				std::cout<<"Congratulations! You made it to the leaderboard!"<<std::endl;
				std::string name;
				std::cout<<"Enter your name: ";
				std::cin>>name;
				leaderboard.addScore(name,maze.getFinalScore(),fileManager.getFileName());
			}
			std::cout<<"Your final score is: "<<maze.getFinalScore()<<std::endl;
			break;
		}
	}

	std::cout<<"Would you like to see path from start to finish?"<<std::endl;
	std::cout<<"1. Yes"<<std::endl;
	std::cout<<"2. No"<<std::endl;

	int path;
	std::cin>>path;

	if (path == 1)
	{
		maze.printPathFromEntranceToExit();
	}
	else if (std::cin.fail())
	{
		std::cout<<"Invalid input, defaulting to not showing path"<<std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	else if (path != 2)
	{
		std::cout<<"Invalid input, defaulting to not showing path"<<std::endl;
	}

	std::cout<<"Goodbye!"<<std::endl;

	return 0;
}