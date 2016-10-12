#ifndef PIDINPUT_H
#define PIDINPUT_H

/**
* An interface that allows classes to provide input to a PidController when implemented.
*/
class PidInput
{
public:
	virtual float getInput() = 0;
};

#endif
