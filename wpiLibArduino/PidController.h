#ifndef PIDCONTROLLER_H
#define PIDCONTROLLER_H

class PidOutput;
class PidInput;

/**
* PidController is an abstract system for controlling some output using feedback from some input. With your Arduino kitbot,
* you can use a PidController to drive a motor based on the infrared range sensor's input.
*/
class PidController
{
private:
	PidOutput* output;
	PidInput* input;
	float p;
	float i;
	float d;
	
	float setpoint;
	
	float accumErr;
	float lastErr;

public:
	PidController(PidOutput* output, PidInput* input, float p, float i, float d);
	
	// Calculates a new output and sends it to the MotorController
	float calculate();
	
	// Clears the accumulated error, sets the setpoint to 0, and stops the motor
	void reset();
	
	// Returns the current target value desired from PidInput
	float getSetpoint();
	
	// Sets the target input value
	void setSetpoint(float setpoint);
};

#endif
