#include <string>
#include <vector>
#include <utility>
#include <fstream>
#include <stdio.h>

#include "GhostGameHandler.h"
#include "GhostPlayer.h"
#include "MyTrie.h"

GhostGameHandler* GhostGameHandler::instance = NULL;

GhostGameHandler::GhostGameHandler()
{
	wordTrie = MyTrie();
	scoreMap = std::map<GhostPlayer*, int>();
}

void GhostGameHandler::readWords(std::string filePath)
{
	std::ifstream file;
	file.open(filePath.c_str());
	char word[32];
	int wordCount = 0;
	while(!file.eof())
	{
		file.getline(word, 32);
		if(word[0] != '\0')
		{
			wordTrie.addDeepChild(std::string(word));
			wordCount++;
		}
	}
	file.close();
	printf("Successfully read %d words\n", wordCount);
}

GhostGameHandler* GhostGameHandler::getInstance()
{
	if(!instance)
	{
		instance = new GhostGameHandler();
	}
	
	return instance;
}

void GhostGameHandler::runGame(std::string wordsFilePath, std::vector<GhostPlayer*> players)
{
	if(!inProgress)
	{
		readWords(wordsFilePath);
		for(int i = 0; i < players.size(); i++)
		{
			scoreMap[players[i]] = 0;
		}
	}
	else
	{
		fprintf(stderr, "Cannot start game while one is running");
	}
}

std::vector<std::pair<std::string, int> > GhostGameHandler::getRemainingPlayers()
{
	std::vector<std::pair<std::string, int> > result = std::vector<std::pair<std::string, int> >();
	for(std::map<GhostPlayer*, int>::iterator i = scoreMap.begin(); i != scoreMap.end(); ++i)
	{
		std::pair<std::string, int> next = std::pair<std::string, int>();
		next.first = i->first->getName();
		next.second = i->second;
		result.push_back(next);
	}
	return result;
}
