#include <StandardCplusplus.h>
#include <system_configuration.h>
#include <unwind-cxx.h>
#include <utility.h>

#include <Adafruit_MotorShield.h>

#include <Command.h>
#include <MotorController.h>
#include <Robot.h>
#include <Scheduler.h>

void setup()
{
  Robot::getInstance()->autonomousInit();
}

void loop()
{
  Robot::getInstance()->autonomousPeriodic();
}
