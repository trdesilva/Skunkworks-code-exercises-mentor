ifeq ($(OS),Windows_NT)
	GTEST_LIB := gtest_win
	SHARED_EXT := dll
else
	GTEST_LIB := gtest
	SHARED_EXT := so
	OS_FLAGS:= -fPIC
endif

all: libpid.$(SHARED_EXT) tests
	g++ main.cpp -L. -lpid -o PIDSim
Motor.o: Constants.h Outputable.h Motor.h Motor.cpp
	g++ $(OS_FLAGS) Constants.h Outputable.h Motor.h Motor.cpp -c
Encoder.o: Motor.o Encoder.h Encoder.cpp
	g++ $(OS_FLAGS) Motor.o Encoder.h Encoder.cpp -c
PIDController.o: Motor.o Encoder.o PIDController.h PIDController.cpp
	g++ $(OS_FLAGS) Motor.o Encoder.o PIDController.h PIDController.cpp -c
libpid.$(SHARED_EXT): Motor.o Encoder.o PIDController.o
	g++ $(OS_FLAGS) -shared Motor.o Encoder.o PIDController.o -o libpid.$(SHARED_EXT)
tests: libpid.$(SHARED_EXT) tests.cpp
	g++ -I. gtest/gtest.h tests.cpp -Lgtest -l$(GTEST_LIB) -L. -lpid -lpthread -o tests
clean:
	rm -f PIDSim tests *.o *.$(SHARED_EXT) *.gch
