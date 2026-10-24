#include "FileManager.h"
#include <ctime>
#include <fstream>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/stat.h>
#include <sys/types.h>
#endif

bool FileManager::folderExists()
{
	#ifdef _WIN32
	DWORD attributes = GetFileAttributesA(folderPath.c_str());
	if (attributes == INVALID_FILE_ATTRIBUTES)
	{
		return false;
	}
	if (attributes & FILE_ATTRIBUTE_DIRECTORY)
	{
		return true;
	}
	return false;
	#else
	struct stat info;
	if (stat(folderPath.c_str(), &info) != 0)
	{
		return false;
	}
	if (info.st_mode & S_IFDIR)
	{
		return true;
	}
	return false;
	#endif
}

void FileManager::createFolder()
{
	#ifdef _WIN32
	CreateDirectoryA(folderPath.c_str(), NULL);
	#else
	mkdir(folderPath.c_str(), 0777);
	#endif
}

void FileManager::generateFile(Maze& maze)
{
	std::time_t now = std::time(nullptr);
	std::tm localTime;
	localtime_s(&localTime, &now);
	char buffer[80];
	strftime(buffer, 80, "%Y-%m-%d_%H-%M-%S", &localTime);
	fileName = "Maze_" + std::string(buffer) + ".txt";
	
	if (!folderExists())
	{
		createFolder();
	}

	std::string filePath = folderPath + "/" + fileName;
	std::ofstream file(filePath);
	
	std::string scoreRecord = maze.getScore();
	file << scoreRecord;

	for (int i = 0; i < maze.getRows(); i++)
	{
		for (int j = 0; j < maze.getCols(); j++)
		{
			file << maze.getMaze()[i][j]<<" ";
		}
		file << std::endl;
	}

	file.close();
}

void FileManager::deleteFiles()
{
	if (folderExists())
	{
		#ifdef _WIN32
		std::string command = "del /Q " + folderPath + "\\*";
		system(command.c_str());
		#else
		std::string command = "rm -rf " + folderPath + "/*";
		system(command.c_str());
		#endif
	}
}

std::string FileManager::readFromFile(std::string fileName)
{
	std::string filePath = folderPath + "/" + fileName;
	std::ifstream file(filePath);

	if (!file.is_open())
	{
		writeToFile(fileName, "");
		return "";
	}

	std::string content;
	std::string line;
	while (std::getline(file, line))
	{
		content += line + "\n";
	}
	file.close();

	return content;
}

void FileManager::writeToFile(std::string fileName, std::string content)
{
	std::string filePath = folderPath + "/" + fileName;
	std::ofstream file(filePath);
	file << content;
	file.close();
}