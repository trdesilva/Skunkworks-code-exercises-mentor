#ifndef ROBOT_H
#define ROBOT_H

#include <string>

class Adafruit_MotorShield;

/**
* The Robot is the top-level class that serves as the entry point for the Arduino sketch.
*/
class Robot
{
private:
	Adafruit_MotorShield* shield;
	
	Robot();
	
public:
	// Get the Robot instance
	static Robot* getInstance();
	
	// Print a log message to the Arduino serial monitor
	void log(std::string message);
	
	// Get the Adafruit_MotorShield instance (used to instantiate MotorControllers; you probably don't need to touch this)
	Adafruit_MotorShield* getShield();
	
	// Called in setup(); use this to instantiate stuff and add your Commands to the Scheduler
	void autonomousInit();
	
	// Called in loop(); calls Scheduler::processCommands() and anything else you might want
	void autonomousPeriodic();
};

#endif
