#include "Command.h"

bool Command::run()
{
	if(!initialized) 
	{
		initialize();
		initialized = true;
	}
	
	bool finished = isFinished();
	if(!finished)
	{
		execute();
	}
	else
	{
		end();
	}
	return finished;
}