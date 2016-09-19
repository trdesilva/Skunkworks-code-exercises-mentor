#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <list>

class Command;

/**
* The Scheduler manages execution of Commands.
*/
class Scheduler
{
private:
	std::list<Command*> commandList;
	
	Scheduler();
	
public:
	// Get the Scheduler instance
	static Scheduler* getInstance();
	
	// Add a command to execute
	void addCommand(Command* command);
	
	// called in Robot::autonomousPeriodic() to run all added Commands
	void processCommands();
};

#endif
