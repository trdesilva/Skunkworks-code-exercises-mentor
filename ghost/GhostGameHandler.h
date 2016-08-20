// Class for running a game of Ghost using multiple GhostPlayers
#ifndef GHOSTGAMEHANDLER_H
#define GHOSTGAMEHANDLER_H

#include <string>
#include <vector>
#include <utility>
#include <map>

#include "MyTrie.h"

#define CHALLENGE_CHAR '?'
#define FORFEIT_CHAR '#'

class GhostPlayer;

class GhostGameHandler
{
private:
	MyTrie wordTrie;
	bool inProgress;
	std::map<GhostPlayer*, int> scoreMap;
	std::vector<GhostPlayer*> playerList;
	
	static GhostGameHandler* instance;
	
	GhostGameHandler();
	
	void readWords(std::string filePath);
	bool babysitThread(pthread_t thread, int timeout);
	int removeLosers();
	void addStrike(GhostPlayer* player);
	
	static void* readWordsTask(void* args);
	static void* getNextLetterTask(void* args);
	
public:
	void runGame(std::string wordsFilePath, std::vector<GhostPlayer*> players, int turnTimeoutSec = 60);
	static GhostGameHandler* getInstance();
	
	std::vector<std::pair<std::string, int> > getRemainingPlayers();
};

struct ThreadArg
{
	GhostPlayer* player;
	std::string* argString;
};

#endif
