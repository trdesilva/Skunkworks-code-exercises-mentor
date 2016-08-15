// Class for running a game of Ghost using multiple GhostPlayers
#include <string>
#include <vector>
#include <utility>

class GhostPlayer;

class GhostGameHandler
{
private:
	std::vector<std::string> wordList;
	GhostGameHandler();
	
public:
	void runGame(std::string wordsFilePath, std::vector<GhostPlayer> players);
	static GhostGameHandler getInstance();
	
	std::vector<std::pair<std::string, int> > getRemainingPlayers();
};