ifeq ($(OS),Windows_NT)
	GTEST_LIB := gtest_win
else
	GTEST_LIB := gtest
endif

all: Motor.o Encoder.o PIDController.o tests
	g++ Motor.o Encoder.o PIDController.o main.cpp -o PIDSim
Motor.o: Constants.h Outputable.h Motor.h Motor.cpp
	g++ Constants.h Outputable.h Motor.h Motor.cpp -c
Encoder.o: Motor.o Encoder.h Encoder.cpp
	g++ Motor.o Encoder.h Encoder.cpp -c
PIDController.o: Motor.o Encoder.o PIDController.h PIDController.cpp
	g++ Motor.o Encoder.o PIDController.h PIDController.cpp -c
tests: Motor.o Encoder.o PIDController.o tests.cpp
	g++ -I. Motor.o Encoder.o PIDController.o gtest/gtest.h tests.cpp -Lgtest -l$(GTEST_LIB) -lpthread -o tests
clean:
	rm -f PIDSim tests *.o *.gch
