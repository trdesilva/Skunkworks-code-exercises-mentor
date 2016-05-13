#include "gtest/gtest.h"
#include "Motor.h"
#include "Encoder.h"
#include "PIDController.h"

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
