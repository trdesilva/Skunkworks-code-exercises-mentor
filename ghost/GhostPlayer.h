// Virtual class for you to use in implementing your own Ghost player
#include <string>

class GhostPlayer
{
public:
	GhostPlayer();
	virtual void readWords(std::string wordsFilePath)=0;
	virtual std::string getNextLetter(std::string currentStr)=0;
	virtual std::string getName()=0;
};