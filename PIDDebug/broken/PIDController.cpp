#include "PIDController.h"
#include <iostream>
#include <cmath>

PIDController::PIDController(Outputable outputable, Encoder encoder, PIDControllerMode mode, double p, double i, double d, double f)
{
    this->outputable = outputable;
    this->encoder = encoder;
    this->mode = mode;
    this->p = p;
    this->i = i;
    this->d = d;
    this->f = f;
    
    setpoint = 0;
    enabled = false;
    lastError = 0;
    sumError = 0;
}

/**
* Advance the PID controller by one time step. Updates the encoder reading and sets the motor output appropriately.
*/
void PIDController::update()
{
    if(enabled)
    {
        encoder.update();
        
        double output = 0;
        double curr;
        if(mode == POSITION_RAW)
        {
            curr = encoder.getRaw();
        }
        else
        {
            curr = encoder.getSpeed();
        }
        double error = curr - setpoint;
        double diffError = lastError - error;
        
        sumError += error;
        output = p*error + (i*sumError)/LOOPS_PER_SEC + (d*diffError)/LOOPS_PER_SEC + f*setpoint;
        lastError = error;
        
        outputable.set(output);
    }
    else
    {
        outputable->set(0);
    }
    
}

/**
* Resets the setpoint and stored error data, and disables the PID.
*/
void PIDController::reset()
{
    setpoint = 0;
    disable();
}

/**
* Enables the PID. Prevents the control mode from being changed.
*/
void PIDController::enable()
{
    enabled = true;
}

/**
* Disables the PID.
*/
void PIDController::disable()
{
    enabled = false;
	outputable.set(0);
}

/**
* Sets the setpoint.
*/
void PIDController::setSetpoint(double setpoint)
{
    this->setpoint = setpoint;
}

/**
* Update the values of P, I, D, and F. F defaults to 0.
*/
void PIDController::setConstants(double p, double i, double d, double f)
{
	this->p = p;
	this->i = i;
	this->d = d;
	this->f = f;
}

/**
* Update the control mode. This changes the value that the PIDController reads from the Encoder in update(). The options are
* POSITION_RAW, POSITION_REV, and SPEED.
*/
void PIDController::setMode(PIDControllerMode mode)
{
	this->mode = mode;
}

/**
* Returns true if the encoder's current state is within an acceptable error margin of the setpoint.
*/
bool PIDController::onTarget() const
{
    if(mode == POSITION_RAW)
    {
        return std::fabs(encoder.getRaw() - setpoint) > POSITION_RAW_TOLERANCE;
    }
    else
    {
        return std::fabs(encoder.getSpeed() - setpoint) > SPEED_TOLERANCE;
    }
}

/**
* Returns the current control mode.
*/
PIDControllerMode PIDController::getMode()
{
	return mode;
}

