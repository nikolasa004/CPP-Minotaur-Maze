#pragma once
#include "Maze.h"
#include <string>
//Nikola Savic, 21.12.2024.

//class for file management
class FileManager
{
private:
	std::string folderPath;
	std::string fileName;
public:
	FileManager(std::string folderPath): folderPath(folderPath) {}

	std::string getFileName() { return fileName; }

	//generates final maze file
	void generateFile(Maze& maze);
	void createFolder();
	bool folderExists();
	void deleteFiles();
	std::string readFromFile(std::string fileName);
	void writeToFile(std::string fileName, std::string content);
};

