#ifndef PIDCONTROLLER_H
#define PIDCONTROLLER_H 1

#include "Outputable.h"
#include "Encoder.h"
#include "Constants.h"

enum PIDControllerMode
{
    POSITION_RAW,
    POSITION_REV,
    SPEED
};

class PIDController
{
private:
    Outputable outputable;
    Encoder encoder;
    PIDControllerMode mode;
    
    double p;
    double i;
    double d;
    double f;
    
    double setpoint;
    bool enabled;
    double lastError;
    double sumError;
    
public:
    PIDController(Outputable outputable, Encoder encoder, PIDControllerMode mode, double p, double i, double d, double f = 0);
    
    void update();
    void reset();
    void enable();
    void disable();
    void setSetpoint(double setpoint);
	void setConstants(double p, double i, double d, double f = 0);
	void setMode(PIDControllerMode mode);
    
    bool onTarget() const;
	PIDControllerMode getMode();
};

#endif

