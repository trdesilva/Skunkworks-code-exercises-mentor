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

class EncoderTest: public ::testing::Test
{
protected:
	Motor* motor;
	Encoder* encoder;
	
	virtual void SetUp()
	{
		motor = new Motor(0);
		encoder = new Encoder(motor);
		encoder->setRandSeed(0);
	}
	
	virtual void TearDown()
	{
		delete encoder;
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

TEST_F(EncoderTest, getSpeedReturnsUpdatedValues)
{
	
}

TEST_F(EncoderTest, getPositionReturnsUpdatedValues)
{
	
}

TEST_F(EncoderTest, getRawReturnsUpdatedValues)
{

}

TEST_F(EncoderTest, resetSetsPositionTo0)
{
	motor->set(1);
	encoder->update();
	encoder->reset(false);
	
	ASSERT_EQ(0, encoder->getRaw());
	ASSERT_EQ(0, encoder->getPosition());
}

TEST_F(EncoderTest, resetObeysSpeedFlag)
{
	motor->set(1);
	encoder->update();
	encoder->reset(false);
	
	double minSpeed = 2*(1./(LOOPS_ACCELERATION + 1))*(1 - (double)ACCURACY_COUNTS/COUNTS_PER_REV)*LOOPS_PER_SEC;
	double maxSpeed = 2*(1./(LOOPS_ACCELERATION + 1))*(1 + (double)ACCURACY_COUNTS/COUNTS_PER_REV)*LOOPS_PER_SEC;
	EXPECT_LE(minSpeed, encoder->getSpeed());
	EXPECT_GE(maxSpeed, encoder->getSpeed());
	
	encoder->reset(true);
	EXPECT_EQ(0, encoder->getSpeed());
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

