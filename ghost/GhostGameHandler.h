// Class for running a game of Ghost using multiple GhostPlayers
#ifndef GHOSTGAMEHANDLER_H
#define GHOSTGAMEHANDLER_H

#include <string>
#include <vector>
#include <utility>
#include <map>

#include "MyTrie.h"

class GhostPlayer;

class GhostGameHandler
{
private:
	MyTrie wordTrie;
	bool inProgress;
	std::map<GhostPlayer*, int> scoreMap;
	GhostGameHandler();
	static GhostGameHandler* instance;
	
	void readWords(std::string filePath);
	
public:
	void runGame(std::string wordsFilePath, std::vector<GhostPlayer*> players);
	static GhostGameHandler* getInstance();
	
	std::vector<std::pair<std::string, int> > getRemainingPlayers();
};
#endif
