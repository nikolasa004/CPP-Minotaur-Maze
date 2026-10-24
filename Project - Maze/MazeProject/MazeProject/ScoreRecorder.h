#pragma once
#include <string>
#include <ctime>
//Nikola Savic, 21.12.2024.

//class that records parameters of the game that affect final score
class ScoreRecorder
{
	int mazeArea;
	int numberOfItems;
	int numberOfMoves;
	int numberOfItemsCollected;
	int numberOfItemsUsed;
	bool enemyKilled;
	std::time_t timeTaken;
	bool gameWon;
	int finalScore;
public:
	ScoreRecorder(int rows, int cols, int numberOfItems): mazeArea(rows*cols), numberOfItems(numberOfItems), numberOfMoves(0), numberOfItemsCollected(0), numberOfItemsUsed(0), enemyKilled(false), gameWon(false),timeTaken(std::time(nullptr)),finalScore(0){}

	int getFinalScore() { return finalScore; }

	void incrementMoves() { numberOfMoves++; }
	void incrementItemsCollected() { numberOfItemsCollected++; }
	void incrementItemsUsed() { numberOfItemsUsed++; }
	void setEnemyKilled() { enemyKilled = true; }
	void setGameWon() { gameWon = true; }

	//calculates final score based on game parameters
	std::string getScore();
};

