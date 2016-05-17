ifeq ($(OS),Windows_NT)
	GTEST_LIB := gtest_win
	SHARED_EXT := dll
else
	GTEST_LIB := gtest
	SHARED_EXT := so
endif

all: libpid.$(SHARED_EXT)
	g++ main.cpp -L. -lpid -o PIDSim
Motor.o: Constants.h Outputable.h Motor.h Motor.cpp
	g++ Constants.h Outputable.h Motor.h Motor.cpp -c
Encoder.o: Motor.o Encoder.h Encoder.cpp
	g++ Motor.o Encoder.h Encoder.cpp -c
PIDController.o: Motor.o Encoder.o PIDController.h PIDController.cpp
	g++ Motor.o Encoder.o PIDController.h PIDController.cpp -c
libpid.$(SHARED_EXT): Motor.o Encoder.o PIDController.o
	g++ -shared Motor.o Encoder.o PIDController.o -o libpid.$(SHARED_EXT)
clean:
	rm -f PIDSim *.o *.$(SHARED_EXT) *.gch
