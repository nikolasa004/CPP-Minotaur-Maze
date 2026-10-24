#include "Leaderboard.h"
#include "FileManager.h"
#include <sstream>

void Leaderboard::readLeaderboard()
{
	FileManager fileManager(folderPath);
	if (!fileManager.folderExists())
	{
		fileManager.createFolder();
		fileManager.writeToFile("Leaderboard.txt", "");
		return;
	}
	std::string content = fileManager.readFromFile("Leaderboard.txt");

	//score format: number|name|score|filename
	std::istringstream stringStream(content);
	std::string line;
	while (std::getline(stringStream, line))
	{
		std::istringstream lineStream(line);

		std::string number;
		std::getline(lineStream, number, '|');

		std::string name;
		std::getline(lineStream, name, '|');

		std::string score;
		std::getline(lineStream, score, '|');

		std::string filename;
		std::getline(lineStream, filename, '|');

		scores[number].push_back(name);
		scores[number].push_back(score);
		scores[number].push_back(filename);
	}
}

bool Leaderboard::checkScore(int finalScore)
{
	if (scores.empty() || scores.size()<10)
	{
		return true;
	}
	for (std::pair<std::string,std::vector<std::string>> score : scores)
	{
		if (std::stoi(score.second[1]) < finalScore)
		{
			return true;
		}
	}
	return false;
}

void Leaderboard::writeLeaderboard()
{
	FileManager fileManager(folderPath);
	std::string content;
	for (std::pair<std::string, std::vector<std::string>> score : scores)
	{
		content += score.first + "|" + score.second[0] + "|" + score.second[1] + "|" + score.second[2] + "\n";
	}
	fileManager.writeToFile("Leaderboard.txt", content);
}

void Leaderboard::addScore(std::string name, int finalScore, std::string filename)
{
	std::string score = std::to_string(finalScore);
	
	int index = 1;
	while (true)
	{
		if (index > scores.size())
		{
			break;
		}
		if (finalScore > std::stoi(scores[std::to_string(index)][1]))
		{
			break;
		}

		index++;
	}

	int startIndex;
	if (scores.size() < 10)
	{
		startIndex = scores.size() + 1;
	}
	else
	{
		startIndex = 10;
	}
	for (int i = startIndex; i > index; i--)
	{
		scores[std::to_string(i)] = scores[std::to_string(i-1)];
	}
	scores[std::to_string(index)].clear();
	scores[std::to_string(index)].push_back(name);
	scores[std::to_string(index)].push_back(score);
	scores[std::to_string(index)].push_back(filename);

	writeLeaderboard();
}