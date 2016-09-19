#include "MotorController.h"
#include "Robot.h"
#include "adafruit/Adafruit_MotorShield.h"

MotorController::MotorController(int port, bool brakeMode)
{
	this->port = port;
	this->brakeMode = brakeMode;
}

void MotorController::setOutput(float output)
{
	uint8_t speed = output*256;
	uint8_t dir;
	if(speed == 0)
	{
		dir = brakeMode ? BRAKE : RELEASE;
	}
	else if(output > 0)
	{
		dir = FORWARD;
	}
	else
	{
		dir = BACKWARD;
	}
	
	Adafruit_DCMotor* motor = Robot::getInstance()->getShield()->getMotor((uint8_t)port);
	motor->setSpeed(speed);
	motor->run(dir);
}

void MotorController::setBrakeMode(bool brake)
{
	this->brakeMode = brake;
}