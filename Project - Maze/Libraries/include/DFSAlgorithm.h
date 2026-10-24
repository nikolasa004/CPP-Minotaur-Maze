#pragma once
#include "MazeGenerator.h"
//Nikola Savic, 18.12.2024.

//Concrete class for maze generation, it uses Randomized Depth First Search algorithm(The backtracking algorithm)
class DFSAlgorithm : public MazeGenerator
{
public :
	DFSAlgorithm(int rows, int cols,int numberOfItems, bool addRooms) :MazeGenerator(rows, cols,numberOfItems,addRooms) {
		generateMaze(addRooms);
	}

	void generateMaze(bool addRooms) override;
};

