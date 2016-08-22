// Class for running a game of Ghost using multiple GhostPlayers
#ifndef GHOSTGAMEHANDLER_H
#define GHOSTGAMEHANDLER_H

#include <string>
#include <vector>
#include <utility>

#define CHALLENGE_CHAR '?'
#define FORFEIT_CHAR '#'
#define READ_WORDS_TIMEOUT_SEC 60

class GhostPlayer;

class GhostGameHandler
{
private:	
	static GhostGameHandler* instance;
	
	GhostGameHandler();
	
public:
	static GhostGameHandler* getInstance();
	void runGame(std::string wordsFilePath, std::vector<GhostPlayer*> players, int turnTimeoutSec = 60);
	std::vector<std::pair<std::string, int> > getRemainingPlayers();
};

#endif
