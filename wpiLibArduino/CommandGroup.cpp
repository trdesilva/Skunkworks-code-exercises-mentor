#include "CommandGroup.h"
#include "Command.h"

#include <list>

CommandGroup::CommandGroup(): commandList()
{
	// no-op
}

void CommandGroup::initialize()
{
	// no-op
}

void CommandGroup::execute()
{
	std::list<Command*> currentSublist = commandList.front();
	Command* nextCommand;
	for(std::list<Command*>::iterator it = currentSublist.begin(); it != currentSublist.end();)
	{
		nextCommand = *it;
		if(!nextCommand->run()) // command is not finished
		{
			it++;
		}
		else
		{
			it = currentSublist.erase(it);
		}
	}
	
	if(currentSublist.empty())
	{
		commandList.pop_front();
	}
}

bool CommandGroup::isFinished()
{
	return commandList.empty();
}

void CommandGroup::end()
{
	// no-op
}

void CommandGroup::addSequential(Command* command)
{
	std::list<Command*> newSublist;
	newSublist.push_front(command);
	commandList.push_back(newSublist);
}

void CommandGroup::addParallel(Command* command)
{
	if(!commandList.empty())
	{
		commandList.back().push_back(command);
	}
	else
	{
		addSequential(command);
	}
}
