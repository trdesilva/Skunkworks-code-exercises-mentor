#include <string>
#include <vector>
#include <utility>
#include <fstream>
#include <stdio.h>
#include <stdexcept>
#include <algorithm>
#include <ctime>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>

#include "GhostGameHandler.h"
#include "GhostPlayer.h"
#include "MyTrie.h"

#define READ_WORDS_TIMEOUT_SEC 60

GhostGameHandler* GhostGameHandler::instance = NULL;

time_t getModifiedTime(std::string filePath)
{
	struct stat s;
	if(stat(filePath.c_str(), &s) == -1)
	{
		fprintf(stderr, "Stat on file %s failed; exiting\n", filePath.c_str());
		exit(EXIT_FAILURE);
	}
	return s.st_mtime;
}

GhostGameHandler::GhostGameHandler()
{
	wordTrie = MyTrie();
	scoreMap = std::map<GhostPlayer*, int>();
}

void GhostGameHandler::readWords(std::string filePath)
{
	std::ifstream file;
	wordsFileModifiedTime = getModifiedTime(filePath);
	file.open(filePath.c_str());
	char word[32];
	int wordCount = 0;
	while(!file.eof())
	{
		file.getline(word, 32);
		if(word[0] != '\0')
		{
			try
			{
				wordTrie.addDeepChild(std::string(word));
			}
			catch(std::invalid_argument e)
			{
				fprintf(stderr, "Word list contains %s, which contains a non-alphabetic character; terminating\n", word);
				file.close();
				exit(EXIT_FAILURE);
			}
			wordCount++;
		}
	}
	file.close();
	printf("Successfully read %d words\n", wordCount);
}

bool GhostGameHandler::babysitProcess(pid_t pid, int timeout)
{
	int status;
	pid_t retVal;
	std::time_t startTime = std::time(NULL);
	bool failure = true;
	while(std::difftime(std::time(NULL), startTime) < timeout)
	{
		retVal = waitpid(pid, &status, WNOHANG);
		if(retVal == 0) // process still working
		{
			usleep(250000);
			continue;
		}
		else if(retVal == pid) // process finished
		{
			if(!status)
			{
				failure = false;
			}
			
			break;
		}
		else //something broke
		{
			break;
		}
	}
	
	if(retVal != pid) //process never came back
	{
		kill(pid, SIGKILL);
	}
	return failure;
}

int GhostGameHandler::removeLosers()
{
	for(int i = 0; i < playerList.size(); i++)
	{
		if(scoreMap[playerList[i]] > 4)
		{
			printf("Player %s has lost\n", playerList[i]->getName().c_str());
			playerList.erase(playerList.begin() + i);
			return i;
		}
	}
	
	return playerList.size();
}

void GhostGameHandler::addStrike(GhostPlayer* player)
{
	static const std::string GHOST = "GHOST";
	scoreMap[player] += 1;
	printf("Player %s now has %s\n", player->getName().c_str(), GHOST.substr(0, scoreMap[player]).c_str());
}

void GhostGameHandler::readWordsTask(GhostPlayer* player, std::string filePath)
{
	try
	{
		player->readWords(filePath);
		printf("Player %s successfully read the word list\n", player->getName().c_str());
		exit(EXIT_SUCCESS);
	}
	catch(...)
	{
		fprintf(stderr, "Player %s threw an exception while reading the word list\n", player->getName().c_str());
		exit(EXIT_FAILURE);
	}
}

void GhostGameHandler::getNextLetterTask(GhostPlayer* player, std::string currWord, int pipeFd)
{
	try
	{
		char letter = tolower(player->getNextLetter(currWord));
		if('a' <= letter && letter <= 'z')
		{
			printf("Player %s successfully chose letter %c\n", player->getName().c_str(), letter);
		}
		else if(letter == CHALLENGE_CHAR)
		{
			printf("Player %s challenges the current string\n", player->getName().c_str());
		}
		else if(letter == FORFEIT_CHAR)
		{
			printf("Player %s forfeits the round\n", player->getName().c_str());
		}
		else
		{
			fprintf(stderr, "Player %s submits invalid letter %c\n", player->getName().c_str(), letter);
			exit(EXIT_FAILURE);
		}
		write(pipeFd, &letter, 1);
		exit(EXIT_SUCCESS);
	}
	catch(...)
	{
		fprintf(stderr, "Player %s threw an exception while choosing a move\n", player->getName().c_str());
		exit(EXIT_FAILURE);
	}
}

GhostGameHandler* GhostGameHandler::getInstance()
{
	if(!instance)
	{
		instance = new GhostGameHandler();
	}
	
	return instance;
}

void GhostGameHandler::runGame(std::string wordsFilePath, std::vector<GhostPlayer*> players, int turnTimeoutSec)
{
	if(!inProgress)
	{
		// setup
		playerList = players; // for use in getRemainingPlayers()
		readWords(wordsFilePath);
		
		for(int i = 0; i < players.size(); i++)
		{
			// use a fork with a timeout to make each player read words
			printf("Starting word list read for player %s\n", players[i]->getName().c_str());
			pid_t pid = fork();
			if(pid == 0) // child
			{
				readWordsTask(players[i], wordsFilePath);
			}
			else if(pid == -1)
			{
				fprintf(stderr, "Failed to create read process for player %s; ending game\n", players[i]->getName().c_str());
				return;
			}
			else
			{
				// monitor child to see if it finishes, cancel if not
				bool failure = babysitProcess(pid, READ_WORDS_TIMEOUT_SEC);
				if(failure)
				{
					printf("Read failed for player %s; kicking from game\n", players[i]->getName().c_str());
					playerList.erase(std::remove(playerList.begin(), playerList.end(), players[i]), playerList.end());
					continue;
				}
			}
			
			if(getModifiedTime(wordsFilePath) != wordsFileModifiedTime)
			{
				fprintf(stderr,
						"Words file at %s has been modified (tampered with by player %s?); exiting\n",
						wordsFilePath.c_str(),
						players[i]->getName().c_str());
				exit(EXIT_FAILURE);
			}
			
			scoreMap[players[i]] = 0;
		}
		
		// game loop
		printf("Starting game with %d players\n", playerList.size());
		int currPlayerIndex = -1;
		std::string currWord = "";
		while(playerList.size() > 1)
		{
			currPlayerIndex = (currPlayerIndex + 1) % playerList.size();
			GhostPlayer* currPlayer = playerList[currPlayerIndex];
			
			// use a fork with a timeout to get each player's move
			printf("Getting next letter from player %s for string \"%s\"\n", currPlayer->getName().c_str(), currWord.c_str());
			int pipes[2];
			pipe(pipes);
			pid_t pid = fork();
			if(pid == 0) // child
			{
				close(pipes[0]);
				getNextLetterTask(currPlayer, currWord, pipes[1]);
			}
			else if(pid == -1)
			{
				fprintf(stderr, "Failed to create move process for player %s; ending game\n", currPlayer->getName().c_str());
				return;
			}
			else
			{
				// monitor child to see if it finishes, cancel if not
				close(pipes[1]);
				bool failure = babysitProcess(pid, turnTimeoutSec);
				if(failure)
				{
					printf("Move failed for player %s; adding strike and starting new round\n", currPlayer->getName().c_str());
					addStrike(currPlayer);
					int removedIndex = removeLosers();
					if(removedIndex <= currPlayerIndex) currPlayerIndex--;
					currWord = "";
					continue;
				}
			}
			
			char letter;
			read(pipes[0], &letter, 1);
			close(pipes[0]);
			if('a' <= letter && letter <= 'z')
			{
				currWord += letter;
			}
			else if(letter == CHALLENGE_CHAR)
			{
				MyTrie* node = wordTrie.getDeepChild(currWord);
				int prevPlayerIndex = (currPlayerIndex == 0) ? playerList.size() - 1 : (currPlayerIndex - 1) % playerList.size();
				GhostPlayer* prevPlayer = playerList[prevPlayerIndex];
				if(node == NULL || node->isTerminal() || !node->hasChildren())
				{
					printf("Player %s successfully challenged player %s over \"%s\"; adding strike to player %s and starting new round\n",
						   currPlayer->getName().c_str(),
						   prevPlayer->getName().c_str(),
						   currWord.c_str(),
						   prevPlayer->getName().c_str());
					addStrike(prevPlayer);
				}
				else
				{
					printf("Player %s unsuccessfully challenged player %s over \"%s\"; adding strike to player %s and starting new round\n",
						   currPlayer->getName().c_str(),
						   prevPlayer->getName().c_str(),
						   currWord.c_str(),
						   currPlayer->getName().c_str());
					addStrike(currPlayer);
				}
				currWord = "";
			}
			else if(letter == FORFEIT_CHAR)
			{
				printf("Adding strike to player %s and starting new round\n", currPlayer->getName().c_str());
				addStrike(currPlayer);
				currWord = "";
			}
			
			int removedIndex = removeLosers();
			if(removedIndex <= currPlayerIndex) currPlayerIndex--;
		}
		
		// teardown
		printf("Player %s wins\n", playerList[0]->getName().c_str());
	}
	else
	{
		fprintf(stderr, "Cannot start game while one is running");
	}
}

std::vector<std::pair<std::string, int> > GhostGameHandler::getRemainingPlayers()
{
	std::vector<std::pair<std::string, int> > result = std::vector<std::pair<std::string, int> >();
	for(int i = 0; i < playerList.size(); i++)
	{
		std::pair<std::string, int> next = std::pair<std::string, int>();
		next.first = playerList[i]->getName();
		next.second = scoreMap[playerList[i]];
		result.push_back(next);
	}
	return result;
}
