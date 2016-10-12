#ifndef COMMAND_H
#define COMMAND_H

/**
* Commands are simple tasks that robots can perform.
*/
class Command
{
private:
	bool initialized = false;
	
public:
	// Called once before execution starts; use for setup (e.g. variable initialization)
	virtual void initialize() = 0;
	
	// Called in a loop while isFinished() returns false
	virtual void execute() = 0;
	
	// Called in a loop to check whether it's time to stop
	virtual bool isFinished() = 0;
	
	// Called once when execution ends; use for teardown (e.g. delete malloc'd stuff)
	virtual void end() = 0;
	
	// Called by Scheduler::processCommands() to handle execution
	bool run();
};

#endif
