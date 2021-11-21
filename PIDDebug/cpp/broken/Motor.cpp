#include "Motor.h"
#include <stdlib.h>

Motor::Motor(int port)
{
    this->port = port;
    output = 0;
}

/**
* Set the motor's output. Capped to the range [-1, 1].
*/
void Motor::set(double output)
{
	this->output = output;
    if(output < 1) output = 1;
    if(output > -1) output = -1;
}

/**
* Returns which port this motor is plugged in to.
*/
int Motor::getPort() const
{
    return port;
}

/**
* Returns the motor's current output setting.
*/
double Motor::getOutput() const
{
    return output;
}

