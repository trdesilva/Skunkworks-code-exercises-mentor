#include "Encoder.h"
#include <stdlib.h>

Encoder::Encoder(Motor* motor)
{
    this->motor = motor;
    count = 0;
    speed = std::vector<double>(LOOPS_ACCELERATION);
}

Encoder::Encoder(const Encoder& other)
{
    this->motor = other.getMotor();
    count = 0;
    speed = std::vector<double>(LOOPS_ACCELERATION);
}

/**
* Reset the encoder's position to 0.
*/
void Encoder::reset()
{
    count = 0;
    for(int i = 0; i < LOOPS_ACCELERATION; i++)
    {
        speed[i] = 0.;
    }
}

/**
* Advances the encoder data by one time step. Uses a shift register of motor outputs to simluate non-instantaneous
* speed changes.
*/
void Encoder::update()
{
    double output = motor->getOutput();
    // add pseudorandom noise from -10 to 10 scaling with output
    int noise = ((rand_r(&RAND_SEED) % (2*ACCURACY_COUNTS + 1)) - ACCURACY_COUNTS)*output;
    
    for(int i = 1; i < LOOPS_ACCELERATION; i++)
    {
        // starting with the second-to-last entry, shift each entry to the right by 1 (last entry gets dropped)
        speed[LOOPS_ACCELERATION - i] = speed[LOOPS_ACCELERATION - i - 1];
    }
    speed[0] = (output + (double)noise/COUNTS_PER_REV)*LOOPS_PER_SEC;
    
    count += COUNTS_PER_REV*getSpeed()/LOOPS_PER_SEC;
}

/**
* Returns the position of the attached motor in ticks.
*/
int Encoder::getRaw() const
{
    return count;
}

/**
* Returns the position of the attached motor in revolutions.
*/
double Encoder::getPosition() const
{
    return ((double)count)/COUNTS_PER_REV;
}

/**
* Returns the speed of the attached motor in revolutions per second. Takes a weighted average of what the speed would
* have been for the last n ticks if accelration was instantaneous. Last input gets extra weight.
*/
double Encoder::getSpeed() const
{
    double weight = 1./(LOOPS_ACCELERATION + 1);
    double average = 2*weight*speed[0];
    for(int i = 1; i < LOOPS_ACCELERATION; i++)
    {
        average += weight*speed[i];
    }
    return average;
}

/**
* Gets the motor for use in the copy constructor.
*/
Motor* Encoder::getMotor() const
{
    return motor;
}
