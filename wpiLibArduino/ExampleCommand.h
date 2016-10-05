#ifndef EXAMPLECOMMAND_H
#define EXAMPLECOMMAND_H

#include "Command.h"
#include "MotorController.h"

class ExampleCommand: public Command
{
private:
	MotorController motorL;
	MotorController motorR;
	
	bool increasing = true;
	float speed = 0;
	unsigned int counter = 0;
	
public:
	ExampleCommand(int portL, int portR);
	
	virtual void initialize();
	virtual void execute();
	virtual bool isFinished();
	virtual void end();
};

#endif
