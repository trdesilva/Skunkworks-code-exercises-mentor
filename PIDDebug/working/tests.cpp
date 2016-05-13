#include "gtest/gtest.h"
#include "Motor.h"
#include "Encoder.h"
#include "PIDController.h"

// Test fixtures
// These are "containers" for groups of tests: they let tests share data setup and teardown methods and data declarations
// so similar tests don't require lots of duplicate work.

class MotorTest: public ::testing::Test
{
protected:
	Motor* motor;	
	
	virtual void SetUp()
	{
		motor = new Motor(0);
	}
	
	virtual void TearDown()
	{
		delete motor;
	}
};

// Tests
// These are function-like macros that run pieces of code and make sure that the right things happen.

TEST_F(MotorTest, outputCanBeSet)
{
	motor->set(0.5);
	EXPECT_EQ(0.5, motor->getOutput());
}

TEST_F(MotorTest, outputCannotExceed100Percent)
{
	motor->set(10);
	EXPECT_EQ(1, motor->getOutput());
	
	motor->set(-10);
	EXPECT_EQ(-1, motor->getOutput());
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
