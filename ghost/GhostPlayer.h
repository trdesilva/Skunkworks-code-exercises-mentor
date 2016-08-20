// Virtual class for you to use in implementing your own Ghost player
#ifndef GHOSTPLAYER_H
#define GHOSTPLAYER_H

#include <string>
class GhostPlayer
{
public:
	GhostPlayer(){};
	virtual void readWords(std::string wordsFilePath)=0;
	virtual char getNextLetter(std::string currentStr)=0;
	virtual std::string getName()=0;
};
#endif
