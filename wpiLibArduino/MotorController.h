#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

/**
* MotorControllers represent the motor controllers on the motor shield, which read a PWM signal from the Arduino and 
* translate it into output current to the motor.
*/
class MotorController
{
private:
	int port;
	bool brakeMode;
	
public:
	// Set port to 1-4 depending on which pins you plugged the motor into on the shield
	MotorController(int port, bool brakeMode = false);
	
	// Takes outputs on the interval [-1, 1] and drives the motor at that percentage of maximum speed
	void setOutput(float output);
	
	// Choose whether the motor controller should be in brake or coast mode (whether the motor stops hard on 0 output)
	void setBrakeMode(bool brake);
};

#endif