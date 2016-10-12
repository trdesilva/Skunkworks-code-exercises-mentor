#ifndef ANALOGINPUT_H
#define ANALOGINPUT_H

#include "PidInput.h"

#include <stdint.h>

/**
* AnalogInput allows you to read the voltages on the Arduino's "Analog In" pins. These can be connected to analog sensors
* that the robot can use to observe its surroundings.
*/
class AnalogInput: public PidInput
{
private:
	uint8_t port;
	
public:
	AnalogInput(uint8_t port);
	
	// Returns the voltage being received
	virtual float getInput();
	uint8_t getPort();
};

#endif