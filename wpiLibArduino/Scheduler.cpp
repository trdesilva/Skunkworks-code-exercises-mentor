#include "Command.h"
#include "Scheduler.h"

#include <list>

Scheduler::Scheduler()
{
	commandList = std::list<Command*>();
}

Scheduler* Scheduler::getInstance()
{
	static Scheduler instance;
	return &instance;
}

void Scheduler::addCommand(Command* command)
{
	commandList.push_back(command);
}

void Scheduler::processCommands()
{
	Command* nextCommand;
	
	for(std::list<Command*>::iterator it = commandList.begin(); it != commandList.end();)
	{
		nextCommand = *it;
		if(!nextCommand->run()) // command is not finished
		{
			it++;
		}
		else
		{
			it = commandList.erase(it);
		}
	}
}