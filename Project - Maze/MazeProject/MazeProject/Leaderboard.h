#pragma once
#include <string>
#include <unordered_map>
#include <vector>
//Nikola Savic, 21.12.2024.

//class that represents the leaderboard
class Leaderboard
{
	std::unordered_map<std::string, std::vector<std::string>> scores;
	std::string folderPath;
public:
	Leaderboard(std::string folderPath) :folderPath(folderPath)
	{
		readLeaderboard();
	}

	void readLeaderboard();
	bool checkScore(int score);
	void addScore(std::string name, int score, std::string filname);
	void writeLeaderboard();
};

