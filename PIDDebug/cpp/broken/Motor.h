#ifndef MOTOR_H
#define MOTOR_H 1

class Motor: public Outputable
{
private:
    int port;
    double output;

public:
    Motor(int port);
    
    void set(double output);
    
    int getPort() const;
    double getOutput() const;
};

#endif

