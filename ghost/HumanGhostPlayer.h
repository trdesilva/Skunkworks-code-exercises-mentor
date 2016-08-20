#include <string>

#include "GhostPlayer.h"

class HumanGhostPlayer: public GhostPlayer
{
private:
	std::string name;
	
public:
	HumanGhostPlayer();
	virtual void readWords(std::string wordsFilePath);
	virtual char getNextLetter(std::string currentStr);
	virtual std::string getName();
};