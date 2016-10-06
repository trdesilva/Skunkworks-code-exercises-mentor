#include "ExampleCommand.h"
#include "MotorController.h"
#include "AnalogInput.h"
#include "Robot.h"
#include "PidController.h"

//#include <sstream>

ExampleCommand::ExampleCommand(int portL, int portR): motorL(portL), motorR(portR), analogInput(0), pidController(&motorL, &analogInput, 1, 0, 0)
{
}

void ExampleCommand::initialize()
{
	motorL.setOutput(0);
	motorR.setOutput(0);
	pidController.setSetpoint(1);
	Robot::getInstance()->log("Starting example command");
}
void ExampleCommand::execute()
{
	//std::stringstream stream;
	//stream << "pidController output: " << pidController.calculate();
	//Robot::getInstance()->log(stream.str());
	/*
	motorL.setOutput(speed);
	motorR.setOutput(speed);
	speed += .001 * (increasing ? 1 : -1);
	if(speed > 1)
	{
		speed = 1;
		increasing = false;
		Robot::getInstance()->log("Speed over 1, decreasing");
	}
	else if(speed < -1)
	{
		speed = -1;
		increasing = true;
		Robot::getInstance()->log("Speed under -1, increasing");
	}
	std::stringstream stream;
	stream << "analog voltage: " << analogInput.getVoltage();
	Robot::getInstance()->log(stream.str());
	*/
}
bool ExampleCommand::isFinished()
{
	return counter++ > 500;
}
void ExampleCommand::end()
{
	Robot::getInstance()->log("Ending example command");
	motorL.setOutput(0);
	motorR.setOutput(0);
	pidController.reset();
}
