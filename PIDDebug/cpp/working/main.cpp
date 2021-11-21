#include "PIDController.h"
#include "Motor.h"
#include "Encoder.h"

#include <iostream>
#include <cmath>

int main(int argc, char** argv)
{
    Motor* motor = new Motor(0);
    Encoder* encoder = new Encoder(motor);
    PIDController* pidController = new PIDController(motor, encoder, POSITION_REV, 1, 0, 0);
    pidController->setSetpoint(10);
    pidController->enable();
    
    Motor* motor2 = new Motor(1);
    Encoder* encoder2 = new Encoder(motor2);
    PIDController* pidController2 = new PIDController(motor2, encoder2, SPEED, 0, 0, 0, .4/20);
    pidController2->setSetpoint(20);
    pidController2->enable();
    
    int ticks = 0;
    
    while(!pidController->onTarget())
    {
        pidController->update();
        pidController2->update();
        std::cout << "tick:\t" << ++ticks << "\tcurrent position:\t" << encoder->getPosition() << "\tcurrent speed:\t" << encoder->getSpeed() << "\n";
        std::cout << "tick:\t" << ticks << "\tcurrent speed:\t" << encoder2->getSpeed() << "\n";
    }
    
    std::cout << "done with position " << encoder->getPosition() << "\n";
    
    return 0;
}
