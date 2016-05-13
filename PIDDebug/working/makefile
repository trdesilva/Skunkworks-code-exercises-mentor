all: PIDSim tests
PIDController.o: Constants.h Outputable.h Motor.h Motor.cpp Encoder.h Encoder.cpp PIDController.h PIDController.cpp
	g++ Constants.h Outputable.h Motor.h Motor.cpp Encoder.h Encoder.cpp PIDController.h PIDController.cpp -c
PIDSim: PIDController.o
	g++ PIDController.o main.cpp -o PIDSim
tests: PIDController.o tests.cpp
	g++ -I. PIDController.o gtest/gtest.h tests.cpp -Lgtest -lgtest -lpthread -o tests
clean:
	rm -f PIDSim tests *.o *.gch
