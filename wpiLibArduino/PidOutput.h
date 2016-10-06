#ifndef PIDOUTPUT_H
#define PIDOUTPUT_H

/**
* An interface that allows classes to receive outputs from a PidController when implemented.
*/
class PidOutput
{
public:
	virtual void setOutput(float output) = 0;
};

#endif
