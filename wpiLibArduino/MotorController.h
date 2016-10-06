#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include "PidOutput.h"

#include <stdint.h>

/**
* MotorControllers represent the motor controllers on the motor shield, which read a PWM signal from the Arduino and 
* translate it into output current to the motor. 
*/
class MotorController: public PidOutput
{
private:
	uint8_t port;
	bool brakeMode;
	
public:
	// Set port to 1-4 depending on which pins you plugged the motor into on the shield
	MotorController(uint8_t port, bool brakeMode = false);
	
	// Takes outputs on the interval [-1, 1] and drives the motor at that percentage of maximum speed
	virtual void setOutput(float output);
	
	// Choose whether the motor controller should be in brake or coast mode (whether the motor stops hard on 0 output)
	void setBrakeMode(bool brake);
};

#endif