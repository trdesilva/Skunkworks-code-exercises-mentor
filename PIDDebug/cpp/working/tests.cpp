#include "gtest/gtest.h"
#include "Motor.h"
#include "Encoder.h"
#include "PIDController.h"

double getInstSpeed(unsigned int* seedPtr, double output);

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
	unsigned int testRandSeed;
	double outputs[LOOPS_ACCELERATION];
	double speeds[LOOPS_ACCELERATION];
	
	virtual void SetUp()
	{
		motor = new Motor(0);
		encoder = new Encoder(motor);
		encoder->setRandSeed(0);
		testRandSeed = 0;
		
		for(int i = 0; i < LOOPS_ACCELERATION; i++)
		{
			int randOutput = (rand_r(&testRandSeed) % 21) - 10;
			outputs[i] = randOutput/10.;
		}
		
		testRandSeed = 0;
		for(int i = 0; i < LOOPS_ACCELERATION; i++)
		{
			speeds[LOOPS_ACCELERATION - 1 - i] = getInstSpeed(&testRandSeed, outputs[i]);
		}
		
		testRandSeed = 0;
	}
	
	virtual void TearDown()
	{
		delete encoder;
		delete motor;
	}
};

class PIDControllerTest: public ::testing::Test
{
protected:
	Motor* motor;
	Encoder* encoder;
	PIDController* pidController;
	
	virtual void SetUp()
	{
		motor = new Motor(0);
		encoder = new Encoder(motor);
		encoder->setRandSeed(0);
		pidController = new PIDController(motor, encoder, POSITION_RAW, 0, 0, 0, 0);
	}
	
	virtual void TearDown()
	{
		delete encoder;
		delete motor;
		delete pidController;
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
	printf("Set output to 10, expecting output 1\n");
	motor->set(10);
	EXPECT_EQ(1, motor->getOutput());
	
	printf("Set output to -10, expecting output -1\n");
	motor->set(-10);
	EXPECT_EQ(-1, motor->getOutput());
}

TEST_F(EncoderTest, getSpeedReturnsUpdatedValues)
{	
	double actualSpeed = 2*(1./(LOOPS_ACCELERATION + 1))*speeds[0];
	for(int i = 1; i < LOOPS_ACCELERATION; i++)
	{
		actualSpeed += (1./(LOOPS_ACCELERATION + 1))*speeds[i];
	}
	
	printf("Sending motor outputs: [ ");
	for(int i = 0; i < LOOPS_ACCELERATION; i++)
	{
		printf("%1.1f ", outputs[i]);
		motor->set(outputs[i]);
		encoder->update();
	}
	printf("]\nExpecting speed %f\n", actualSpeed);
	ASSERT_EQ(actualSpeed, encoder->getSpeed());
}

TEST_F(EncoderTest, getPositionReturnsUpdatedValues)
{
	int actualTicks = COUNTS_PER_REV*((2*(1./(LOOPS_ACCELERATION + 1))*speeds[LOOPS_ACCELERATION - 1])/LOOPS_PER_SEC);
	double actualPos = (double)actualTicks/COUNTS_PER_REV;
	motor->set(outputs[0]);
	encoder->update();
	printf("Set output to %f, expecting position %f\n", outputs[0], actualPos);
	
	ASSERT_EQ(actualPos, encoder->getPosition());
	
	actualTicks += COUNTS_PER_REV*(2*(1./(LOOPS_ACCELERATION + 1))*speeds[LOOPS_ACCELERATION - 2] + (1./(LOOPS_ACCELERATION + 1))*speeds[LOOPS_ACCELERATION - 1])/LOOPS_PER_SEC;
	actualPos = (double)actualTicks/COUNTS_PER_REV;
	motor->set(outputs[1]);
	encoder->update();
	printf("Set output to %f, expecting position %f\n", outputs[1], actualPos);
	
	ASSERT_EQ(actualPos, encoder->getPosition());
}

TEST_F(EncoderTest, getRawReturnsUpdatedValues)
{
	int actualTicks = COUNTS_PER_REV*((2*(1./(LOOPS_ACCELERATION + 1))*speeds[LOOPS_ACCELERATION - 1])/LOOPS_PER_SEC);
	motor->set(outputs[0]);
	encoder->update();
	printf("Set output to %f, expecting count %d\n", outputs[0], actualTicks);
	
	ASSERT_EQ(actualTicks, encoder->getRaw());
	
	actualTicks += COUNTS_PER_REV*(2*(1./(LOOPS_ACCELERATION + 1))*speeds[LOOPS_ACCELERATION - 2] + (1./(LOOPS_ACCELERATION + 1))*speeds[LOOPS_ACCELERATION - 1])/LOOPS_PER_SEC;
	motor->set(outputs[1]);
	encoder->update();
	printf("Set output to %f, expecting count %d\n", outputs[1], actualTicks);
	
	ASSERT_EQ(actualTicks, encoder->getRaw());
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
	printf("Reset position without resetting speed, expect nonzero speed\n");
	EXPECT_LT(0, encoder->getSpeed());
	
	encoder->reset(true);
	printf("Reset position and speed, expect 0 speed\n");
	EXPECT_EQ(0, encoder->getSpeed());
}

TEST_F(EncoderTest, updateUsesCorrectAmountOfRandomness)
{
	motor->set(1);
	encoder->update();
	
	double speed = 2*(1./(LOOPS_ACCELERATION + 1))*getInstSpeed(&testRandSeed, 1);
	printf("Output set to 1, expect speed %f\n", speed);
	ASSERT_EQ(speed, encoder->getSpeed());
}

TEST_F(PIDControllerTest, basicVerificationTest)
{
	int loops = 0;
	int onTargetLoops = 0;
	// Check that position mode works as expected
	printf("Setting PIDF values to [ 1 0.001 0.01 0 ]\n");
	pidController->setConstants(1, 0.001, .01, 0);
	printf("Setting setpoint to 10 revolutions\n");
	pidController->setSetpoint(10);
	pidController->setMode(POSITION_REV);
	
	pidController->enable();
	while(onTargetLoops < 10)
	{
		pidController->update();
		
		if(pidController->onTarget())
		{
			onTargetLoops++;
		}
		else if(onTargetLoops > 0)
		{
			onTargetLoops--;
		}
		
		loops++;
	}
	
	printf("Verifying that PID took 97 loops to settle\n");
	EXPECT_EQ(97, loops);
	
	printf("Verifying that encoder position is within tolerance\n");
	EXPECT_LT(10 - POSITION_REV_TOLERANCE, encoder->getPosition());
	EXPECT_GT(10 + POSITION_REV_TOLERANCE, encoder->getPosition());
	
	printf("Resetting PIDController and encoder for next test\n");
	pidController->reset();
	encoder->reset(true);
	encoder->setRandSeed(0);
	loops = 0;
	onTargetLoops = 0;
	
	// Check that raw position mode works as expected
	printf("Setting PIDF values to [ 0.001 0.000001 0.001 0 ]\n");
	pidController->setConstants(.001, 0.000001, .001, 0);
	printf("Setting setpoint to 10240 ticks\n");
	pidController->setSetpoint(10240);
	pidController->setMode(POSITION_RAW);
	
	pidController->enable();
	while(onTargetLoops < 10)
	{
		pidController->update();
		
		if(pidController->onTarget())
		{
			onTargetLoops++;
		}
		else if(onTargetLoops > 0)
		{
			onTargetLoops--;
		}
		
		loops++;
	}
	
	printf("Verifying that PID took 104 loops to settle\n");
	EXPECT_EQ(104, loops);
	
	printf("Verifying that encoder position is within tolerance\n");
	EXPECT_LT(10240 - POSITION_RAW_TOLERANCE, encoder->getRaw());
	EXPECT_GT(10240 + POSITION_RAW_TOLERANCE, encoder->getRaw());
	
	printf("Resetting PIDController and encoder for next test\n");
	pidController->reset();
	encoder->reset(true);
	encoder->setRandSeed(0);
	loops = 0;
	onTargetLoops = 0;
	
	// Check that speed mode works as expected
	printf("Setting PIDF values to [ 0.01 0.1 0.00001 0.01 ]\n");
	pidController->setConstants(.01, 0.1, .00001, 0.01);
	printf("Setting setpoint to 10 revolutions per second\n");
	pidController->setSetpoint(10);
	pidController->setMode(SPEED);
	
	pidController->enable();
	while(onTargetLoops < 10)
	{
		pidController->update();
		
		if(pidController->onTarget())
		{
			onTargetLoops++;
		}
		else if(onTargetLoops > 0)
		{
			onTargetLoops--;
		}
		
		loops++;
	}
	
	printf("Verifying that PID took 32 loops to settle\n");
	EXPECT_EQ(32, loops);
	
	printf("Verifying that encoder position is within tolerance\n");
	EXPECT_LT(10 - SPEED_TOLERANCE, encoder->getSpeed());
	EXPECT_GT(10 + SPEED_TOLERANCE, encoder->getSpeed());
	
	printf("Resetting PIDController and encoder for next test\n");
	pidController->reset();
	encoder->reset(true);
	encoder->setRandSeed(0);
	loops = 0;
	onTargetLoops = 0;
	
	// Check that PID doesn't run when disabled
	printf("Verifying that PID can't run while disabled\n");
	pidController->update();
	EXPECT_EQ(0, motor->getOutput());
	
	// Check that mode can't be changed when PID is enabled
	printf("Verifying that control mode can't be changed while PID is running\n");
	pidController->enable();
	pidController->setMode(POSITION_RAW);
	
	ASSERT_EQ(SPEED, pidController->getMode());
}

double getInstSpeed(unsigned int* seedPtr, double output)
{
	int noise = ((rand_r(seedPtr) % (2*ACCURACY_COUNTS + 1)) - ACCURACY_COUNTS)*output;
	return (output + (double)noise/COUNTS_PER_REV)*LOOPS_PER_SEC;
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	int fail = RUN_ALL_TESTS();
	if(!fail)
	{
		printf("\n\n******************************\n* Congratulations, it works! *\n******************************\n");
	}
	return fail;
}

