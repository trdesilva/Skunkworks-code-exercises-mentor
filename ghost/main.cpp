#include "MyTrie.h"
#include "GhostGameHandler.h"
#include <iostream>
#include <vector>

int main(int argc, char** argv)
{
	GhostGameHandler::getInstance()->runGame("words.txt", std::vector<GhostPlayer*>());
	return 0;
}
