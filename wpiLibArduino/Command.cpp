#include "Command.h"

bool Command::run()
{
	if(!initialized) initialize();
	
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