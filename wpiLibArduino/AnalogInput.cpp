#include "AnalogInput.h"

#include <arduino.h>
#include <stdint.h>

#define ANALOGINPUT_RESOLUTION 1024.

AnalogInput::AnalogInput(uint8_t port)
{
	this->port = port;
}

float AnalogInput::getInput()
{
	return analogRead(this->port)/ANALOGINPUT_RESOLUTION;
}

uint8_t AnalogInput::getPort()
{
	return this->port;
}
