#ifndef ENCODER_H
#define ENCODER_H 1

#include "Motor.h"
#include "Constants.h"

#include <vector>

static unsigned int RAND_SEED = 0;

class Encoder
{
private:
    Motor* motor;
    
    int count;
    std::vector<double> speed;
    
public:
    Encoder(Motor* motor);
    Encoder(const Encoder& encoder);
    
    void reset();
    void update();
    
    int getRaw() const;
    double getPosition() const;
    double getSpeed() const;
    
    Motor* getMotor() const;
};

#endif

