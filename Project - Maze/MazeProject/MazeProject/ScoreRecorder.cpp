#include "ScoreRecorder.h"
#include <string>

std::string ScoreRecorder::getScore()
{
	std::string scoreContent;

	int score=0;

	score+=mazeArea;
	scoreContent+="Maze area: "+std::to_string(mazeArea)+"\n";

	score-=numberOfItems*5;
	scoreContent+="Number of items: "+std::to_string(numberOfItems)+"\n";

	score-=numberOfMoves*2;
	scoreContent+="Number of moves: "+std::to_string(numberOfMoves)+"\n";

	int itemsNotCollected = numberOfItems - numberOfItemsCollected;
	score-=itemsNotCollected*3;
	scoreContent+="Number of items not collected: "+std::to_string(itemsNotCollected)+"\n";

	score+=numberOfItemsUsed*2;
	scoreContent+="Number of items used: "+std::to_string(numberOfItemsUsed)+"\n";

	if (enemyKilled)
	{
		score*=2;
	}
	scoreContent+="Enemy killed: "+std::to_string(enemyKilled)+"\n";

	if (gameWon)
	{
		score*=2;
	}
	scoreContent+="Game won: "+std::to_string(gameWon)+"\n";

	std::time_t	endTime = std::time(nullptr);
	int time = endTime - timeTaken;
	score-=time;
	scoreContent+="Time taken: "+std::to_string(time)+"\n"+"\n";

	scoreContent+="Final score: "+std::to_string(score)+"\n";
	finalScore=score;

	return scoreContent;
}