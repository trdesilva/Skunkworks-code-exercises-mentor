#ifndef COMMANDGROUP_H
#define COMMANDGROUP_H

#include "Command.h"

#include <list>

class CommandGroup: public Command
{
private:
	std::list<std::list<Command*> > commandList;
	
public:
	CommandGroup();

	virtual void initialize();
	virtual void execute();
	virtual bool isFinished();
	virtual void end();
	
	// Add a command to be executed after the last command in the list finishes
	void addSequential(Command* command);
	
	// Add a command to be executed at the same time as the last command
	void addParallel(Command* command);
};

#endif