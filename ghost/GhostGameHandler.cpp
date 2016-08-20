#include <string>
#include <vector>
#include <utility>
#include <fstream>
#include <stdio.h>
#include <pthread.h>
#include <exception>
#include <algorithm>
#include <ctime>
#include <errno.h>
#include <unistd.h>

#include "GhostGameHandler.h"
#include "GhostPlayer.h"
#include "MyTrie.h"

#define READ_WORDS_TIMEOUT_SEC 5

GhostGameHandler* GhostGameHandler::instance = NULL;
pthread_mutex_t mutex;

GhostGameHandler::GhostGameHandler()
{
	wordTrie = MyTrie();
	scoreMap = std::map<GhostPlayer*, int>();
}

void GhostGameHandler::readWords(std::string filePath)
{
	std::ifstream file;
	file.open(filePath.c_str());
	char word[32];
	int wordCount = 0;
	while(!file.eof())
	{
		file.getline(word, 32);
		if(word[0] != '\0')
		{
			wordTrie.addDeepChild(std::string(word));
			wordCount++;
		}
	}
	file.close();
	printf("Successfully read %d words\n", wordCount);
}

bool GhostGameHandler::babysitThread(pthread_t thread, int timeout)
{
	void* status;
	int retVal;
	std::time_t startTime = std::time(NULL);
	bool failure = true;
	while(std::difftime(std::time(NULL), startTime) < timeout)
	{
		retVal = pthread_mutex_trylock(&mutex);
		if(retVal == EBUSY) // thread still working
		{
			usleep(250000);
			continue;
		}
		else if(retVal == 0) // thread finished
		{
			retVal = pthread_join(thread, &status);
			if(!(retVal || status))
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

void* GhostGameHandler::readWordsTask(void* args)
{
	ThreadArg* threadArg = (ThreadArg*)args;
	try
	{
		pthread_mutex_lock(&mutex);
		threadArg->player->readWords(*(threadArg->argString));
		printf("Player %s successfully read the word list\n", threadArg->player->getName().c_str());
		pthread_mutex_unlock(&mutex);
		pthread_exit(NULL);
	}
	catch(...)
	{
		printf("Player %s threw an exception while reading the word list\n", threadArg->player->getName().c_str());
		pthread_mutex_unlock(&mutex);
		pthread_exit((void*)1);
	}
}

void* GhostGameHandler::getNextLetterTask(void* args)
{
	ThreadArg* threadArg = (ThreadArg*)args;
	try
	{
		pthread_mutex_lock(&mutex);
		char letter = threadArg->player->getNextLetter(*(threadArg->argString));
		if('a' <= letter && letter <= 'z')
		{
			printf("Player %s successfully chose letter %c\n", threadArg->player->getName().c_str(), letter);
		}
		else if(letter == CHALLENGE_CHAR)
		{
			printf("Player %s challenges the current string\n", threadArg->player->getName().c_str());
		}
		else if(letter == FORFEIT_CHAR)
		{
			printf("Player %s forfeits the round\n", threadArg->player->getName().c_str());
		}
		else
		{
			printf("Player %s submits invalid letter %c\n", threadArg->player->getName().c_str(), letter);
			pthread_mutex_unlock(&mutex);
			pthread_exit((void*)1);
		}
		*(threadArg->argString) += letter;
		pthread_mutex_unlock(&mutex);
		pthread_exit(NULL);
	}
	catch(...)
	{
		printf("Player %s threw an exception while choosing a move\n", threadArg->player->getName().c_str());
		pthread_mutex_unlock(&mutex);
		pthread_exit((void*)1);
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
			// use a thread with a timeout to make each player read words
			pthread_t readThread;
			pthread_mutex_init(&mutex, NULL);
			ThreadArg readThreadArg = ThreadArg();
			readThreadArg.player = players[i];
			readThreadArg.argString = &wordsFilePath;
			printf("Starting word list read for player %s\n", players[i]->getName().c_str());
			pthread_attr_t attr;
			pthread_attr_init(&attr);
			pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
			int retVal = pthread_create(&readThread, &attr, readWordsTask, (void*)&readThreadArg);
			if(retVal)
			{
				printf("Read failed for player %s, kicking from game\n", players[i]->getName().c_str());
				playerList.erase(std::remove(playerList.begin(), playerList.end(), players[i]), playerList.end());
				// TODO apparently pthread_cancel() doesn't work in C++; replace with pthread_kill() and signal handling
				pthread_cancel(readThread);
				pthread_mutex_destroy(&mutex);
				continue;
			}
			usleep(1); // yield to new thread so it can start
			
			// monitor thread to see if it finishes, cancel if not
			bool failure = babysitThread(readThread, READ_WORDS_TIMEOUT_SEC);
			
			pthread_attr_destroy(&attr);
			pthread_mutex_destroy(&mutex);
			
			if(failure)
			{
				printf("Read failed for player %s, kicking from game\n", players[i]->getName().c_str());
				playerList.erase(std::remove(playerList.begin(), playerList.end(), players[i]), playerList.end());
				pthread_cancel(readThread);
				continue;
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
			
			// use a thread with a timeout to get each player's move
			pthread_t moveThread;
			pthread_mutex_init(&mutex, NULL);
			ThreadArg moveThreadArg = ThreadArg();
			moveThreadArg.player = currPlayer;
			moveThreadArg.argString = &currWord;
			printf("Getting next letter from player %s for string \"%s\"\n", currPlayer->getName().c_str(), currWord.c_str());
			pthread_attr_t attr;
			pthread_attr_init(&attr);
			pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
			int retVal = pthread_create(&moveThread, &attr, getNextLetterTask, (void*)&moveThreadArg);
			if(retVal)
			{
				printf("Move failed for player %s, adding strike and starting new round\n", currPlayer->getName().c_str());
				addStrike(currPlayer);
				pthread_cancel(moveThread);
				pthread_mutex_destroy(&mutex);
				int removedIndex = removeLosers();
				if(removedIndex <= currPlayerIndex) currPlayerIndex--;
				currWord = "";
				continue;
			}
			usleep(1); // yield to new thread so it can start
			
			// monitor thread to see if it finishes, cancel if not
			bool failure = babysitThread(moveThread, turnTimeoutSec);
			
			pthread_attr_destroy(&attr);
			pthread_mutex_destroy(&mutex);
			
			if(failure)
			{
				printf("Move failed for player %s, adding strike and starting new round\n", currPlayer->getName().c_str());
				addStrike(currPlayer);
				pthread_cancel(moveThread);
				int removedIndex = removeLosers();
				if(removedIndex <= currPlayerIndex) currPlayerIndex--;
				currWord = "";
				continue;
			}
			
			char letter = currWord[currWord.size() - 1];
			if('a' <= letter && letter <= 'z')
			{
				// no-op
			}
			else if(letter == CHALLENGE_CHAR)
			{
				std::string prevWord = currWord.substr(0, currWord.size() - 1);
				MyTrie* node = wordTrie.getDeepChild(prevWord);
				int prevPlayerIndex = (currPlayerIndex == 0) ? playerList.size() - 1 : (currPlayerIndex - 1) % playerList.size();
				GhostPlayer* prevPlayer = playerList[prevPlayerIndex];
				if(node == NULL || node->isTerminal() || !node->hasChildren())
				{
					printf("Player %s successfully challenged player %s over \"%s\"; adding strike to player %s and starting new round\n",
						   currPlayer->getName().c_str(),
						   prevPlayer->getName().c_str(),
						   prevWord.c_str(),
						   prevPlayer->getName().c_str());
					addStrike(prevPlayer);
				}
				else
				{
					printf("Player %s unsuccessfully challenged player %s over \"%s\"; adding strike to player %s and starting new round\n",
						   currPlayer->getName().c_str(),
						   prevPlayer->getName().c_str(),
						   prevWord.c_str(),
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
