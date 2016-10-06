#include "PidController.h"
#include "PidOutput.h"
#include "PidInput.h"

PidController::PidController(PidOutput* output, PidInput* input, float p, float i, float d)
{
	this->output = output;
	this->input = input;
	this->p = p;
	this->i = i;
	this->d = d;
	
	this->setpoint = 0;
	
	this->accumErr = 0;
	this->lastErr = 0;
}

float PidController::calculate()
{
	float err = setpoint - input->getInput();
	accumErr += err;
	float out = p*err + i*accumErr + d*(lastErr - err);
	lastErr = err;
	output->setOutput(out);
	return out;
}

void PidController::reset()
{
	setpoint = 0;
	accumErr = 0;
	lastErr = 0;
	output->setOutput(0);
}

float PidController::getSetpoint()
{
	return setpoint;
}

void PidController::setSetpoint(float setpoint)
{
	this->setpoint = setpoint;
}
