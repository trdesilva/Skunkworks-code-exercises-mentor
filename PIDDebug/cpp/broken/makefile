ifeq ($(OS),Windows_NT)
	GTEST_LIB := gtest_win
	SHARED_EXT := dll
else
	GTEST_LIB := gtest
	SHARED_EXT := so
	OS_FLAGS := -fPIC
endif

all: libpid.$(SHARED_EXT)
	g++ main.cpp -L. -lpid -o PIDSim
Motor.o: Constants.h Outputable.h Motor.h Motor.cpp
	g++ $(OS_FLAGS) Constants.h Outputable.h Motor.h Motor.cpp -c
Encoder.o: Motor.o Encoder.h Encoder.cpp
	g++ $(OS_FLAGS) Motor.o Encoder.h Encoder.cpp -c
PIDController.o: Motor.o Encoder.o PIDController.h PIDController.cpp
	g++ $(OS_FLAGS) Motor.o Encoder.o PIDController.h PIDController.cpp -c
libpid.$(SHARED_EXT): Motor.o Encoder.o PIDController.o
	g++ $(OS_FLAGS) -shared Motor.o Encoder.o PIDController.o -o libpid.$(SHARED_EXT)
clean:
	rm -f PIDSim *.o *.$(SHARED_EXT) *.gch
