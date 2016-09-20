LIB_DIR=/cygdrive/d/Documents/Arduino/libraries
LIB_NAME=WpiLib-Arduino

all: clean project

clean:
	rm -r $(LIB_DIR)/$(LIB_NAME)

project: Command.h ExampleCommand.h library.properties MotorController.h Robot.h Scheduler.h Command.cpp ExampleCommand.cpp keywords.txt MotorController.cpp Robot.cpp Scheduler.cpp
	mkdir $(LIB_DIR)/$(LIB_NAME)
	cp Command.h ExampleCommand.h library.properties MotorController.h Robot.h Scheduler.h Command.cpp ExampleCommand.cpp keywords.txt MotorController.cpp Robot.cpp Scheduler.cpp $(LIB_DIR)/$(LIB_NAME)
	cp -r adafruit $(LIB_DIR)/$(LIB_NAME)