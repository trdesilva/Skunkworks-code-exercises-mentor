#include <iostream>
#include <string>

#include "HumanGhostPlayer.h"

HumanGhostPlayer::HumanGhostPlayer()
{
	std::cout << "Name?\n";
	std::cin >> name;
}

void HumanGhostPlayer::readWords(std::string wordsFilePath)
{
	// no-op, people don't need this
}

char HumanGhostPlayer::getNextLetter(std::string currentStr)
{
	std::cout << "Current string: \"" << currentStr << "\"\nNext letter: ";
	char next;
	std::cin.clear();
	std::cin >> next;
	return next;
}

std::string HumanGhostPlayer::getName()
{
	return name;
}
