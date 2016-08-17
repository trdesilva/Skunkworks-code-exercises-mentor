#include <string>
#include <vector>
#include <utility>

#include "GhostGameHandler.h"
#include "GhostPlayer.h"
#include "MyTrie.h"

GhostGameHandler* GhostGameHandler::instance = NULL;

GhostGameHandler::GhostGameHandler()
{
	wordTrie = MyTrie();
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
	
}

std::vector<std::pair<std::string, int> > GhostGameHandler::getRemainingPlayers()
{
	return std::vector<std::pair<std::string, int> >();
}
