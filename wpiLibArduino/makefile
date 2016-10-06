LIB_DIR=/cygdrive/d/Documents/Arduino/libraries
LIB_NAME=WpiLib-Arduino

all: clean project

clean:
	rm -r $(LIB_DIR)/$(LIB_NAME)

project: Command.h CommandGroup.h ExampleCommand.h MotorController.h Robot.h Scheduler.h AnalogInput.h PidController.h PidOutput.h PidInput.h Command.cpp CommandGroup.cpp ExampleCommand.cpp keywords.txt MotorController.cpp Robot.cpp Scheduler.cpp AnalogInput.cpp PidController.cpp library.properties
	mkdir $(LIB_DIR)/$(LIB_NAME)
	cp Command.h CommandGroup.h ExampleCommand.h MotorController.h Robot.h Scheduler.h AnalogInput.h PidController.h PidOutput.h PidInput.h Command.cpp CommandGroup.cpp ExampleCommand.cpp keywords.txt MotorController.cpp Robot.cpp Scheduler.cpp AnalogInput.cpp PidController.cpp library.properties $(LIB_DIR)/$(LIB_NAME)
	cp -r adafruit $(LIB_DIR)/$(LIB_NAME)