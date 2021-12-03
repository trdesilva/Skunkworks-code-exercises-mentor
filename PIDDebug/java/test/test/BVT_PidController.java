package test;

import org.hamcrest.MatcherAssert;
import org.junit.Before;
import org.junit.Test;
import src.Constants;
import src.Encoder;
import src.Motor;
import src.PidController;

import static org.hamcrest.CoreMatchers.is;
import static org.hamcrest.MatcherAssert.assertThat;
import static org.junit.Assert.assertTrue;

public class BVT_PidController
{
    private Motor motor;
    private Encoder encoder;
    private PidController pidController;
    
    @Before
    public void setup()
    {
        motor = new Motor(0);
        encoder = new Encoder(motor);
        encoder.setRandSeed(0);
        pidController = new PidController(motor, encoder, PidController.Mode.POSITION_RAW, 0, 0, 0, 0);
    }
    
    @Test
    public void doTest()
    {
        int loops = 0;
        int onTargetLoops = 0;
        // Check that position mode works as expected
        System.out.println("Setting PIDF values to [ 1 0.001 0.01 0 ]");
        pidController.setConstants(1, 0.001, .01, 0);
        System.out.println("Setting setpoint to 10 revolutions");
        pidController.setSetpoint(10);
        pidController.setMode(PidController.Mode.POSITION_REV);
    
        pidController.enable();
        while(onTargetLoops < 10 && loops < 1000)
        {
            pidController.update();
        
            if(pidController.onTarget())
            {
                onTargetLoops++;
            }
            else if(onTargetLoops > 0)
            {
                onTargetLoops--;
            }
        
            loops++;
        }
    
        System.out.println("Verifying that PID took 97 loops to settle");
        assertThat("PID should have taken 97 loops to settle", loops, is(97));
    
        System.out.println("Verifying that encoder position is within tolerance");
        assertTrue("Encoder position should be above minimum threshold", 10 - Constants.POSITION_REV_TOLERANCE < encoder.getPosition());
        assertTrue("Encoder position should be below maximum threshold", 10 + Constants.POSITION_REV_TOLERANCE > encoder.getPosition());
    
        System.out.println("Resetting PidController and encoder for next test");
        pidController.reset();
        encoder.reset(true);
        encoder.setRandSeed(0);
        loops = 0;
        onTargetLoops = 0;
    
        // Check that raw position mode works as expected
        System.out.println("Setting PIDF values to [ 0.001 0.000001 0.001 0 ]");
        pidController.setConstants(.001, 0.000001, .001, 0);
        System.out.println("Setting setpoint to 10240 ticks");
        pidController.setSetpoint(10240);
        pidController.setMode(PidController.Mode.POSITION_RAW);
    
        pidController.enable();
        while(onTargetLoops < 10 && loops < 1000)
        {
            pidController.update();
        
            if(pidController.onTarget())
            {
                onTargetLoops++;
            }
            else if(onTargetLoops > 0)
            {
                onTargetLoops--;
            }
        
            loops++;
        }
    
        System.out.println("Verifying that PID took 104 loops to settle");
        assertThat("PID should have taken 104 loops to settle", loops, is(104));
    
        System.out.println("Verifying that encoder position is within tolerance");
        assertTrue("Encoder raw count should be above minimum threshold", 10240 - Constants.POSITION_RAW_TOLERANCE < encoder.getRaw());
        assertTrue("Encoder raw count should be below maximum threshold", 10240 + Constants.POSITION_RAW_TOLERANCE > encoder.getRaw());
    
        System.out.println("Resetting PidController and encoder for next test");
        pidController.reset();
        encoder.reset(true);
        encoder.setRandSeed(0);
        loops = 0;
        onTargetLoops = 0;
    
        // Check that speed mode works as expected
        System.out.println("Setting PIDF values to [ 0.01 0.1 0.00001 0.01 ]");
        pidController.setConstants(.01, 0.1, .00001, 0.01);
        System.out.println("Setting setpoint to 10 revolutions per second");
        pidController.setSetpoint(10);
        pidController.setMode(PidController.Mode.SPEED);
    
        pidController.enable();
        while(onTargetLoops < 10 && loops < 1000)
        {
            pidController.update();
        
            if(pidController.onTarget())
            {
                onTargetLoops++;
            }
            else if(onTargetLoops > 0)
            {
                onTargetLoops--;
            }
        
            loops++;
        }
    
        System.out.println("Verifying that PID took 35 loops to settle");
        assertThat("PID should have taken 35 loops to settle", loops, is(35));
    
        System.out.println("Verifying that encoder position is within tolerance");
        assertTrue("Encoder speed should be above minimum threshold", 10 - Constants.SPEED_TOLERANCE < encoder.getSpeed());
        assertTrue("Encoder speed should be below maximum threshold", 10 + Constants.SPEED_TOLERANCE > encoder.getSpeed());
    
        System.out.println("Resetting PidController and encoder for next test");
        pidController.reset();
        encoder.reset(true);
        encoder.setRandSeed(0);
    
        // Check that PID doesn't run when disabled
        System.out.println("Verifying that PID can't run while disabled");
        pidController.update();
        MatcherAssert.assertThat(motor.getOutput(), is(0.));
    
        // Check that mode can't be changed when PID is enabled
        System.out.println("Verifying that control mode can't be changed while PID is running");
        pidController.enable();
        pidController.setMode(PidController.Mode.POSITION_RAW);
    
        assertThat("PidController should still be in SPEED mode", pidController.getMode(), is(PidController.Mode.SPEED));
    }
}
