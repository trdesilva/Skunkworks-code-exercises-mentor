#include "Robot.h"
#include "Scheduler.h"
#include "adafruit/Adafruit_MotorShield.h"
#include <Wire.h>
#include "ExampleCommand.h"

#include <string>

Robot::Robot()
{
	shield = new Adafruit_MotorShield();
	shield->begin();
	Serial.begin(9600);
}

Robot* Robot::getInstance()
{
	static Robot instance;
	return &instance;
}

void Robot::log(std::string message)
{
	Serial.println(message.c_str());
}

Adafruit_MotorShield* Robot::getShield()
{
	return shield;
}

void Robot::autonomousInit()
{
	// TODO your code here
	Scheduler::getInstance()->addCommand(new ExampleCommand(4, 3));
}

void Robot::autonomousPeriodic()
{
	Scheduler::getInstance()->processCommands();
}
