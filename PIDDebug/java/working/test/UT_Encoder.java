import org.junit.Before;
import org.junit.Test;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

import static org.hamcrest.CoreMatchers.is;
import static org.hamcrest.MatcherAssert.assertThat;
import static org.junit.Assert.assertTrue;

public class UT_Encoder
{
    private Motor motor;
    private Encoder encoder;
    List<Double> outputs;
    List<Double> speeds;
    
    @Before
    public void setup()
    {
        motor = new Motor(0);
        encoder = new Encoder(motor);
        encoder.setRandSeed(0);
        Random random = new Random(0);
        
        outputs = new ArrayList<>(Constants.LOOPS_ACCELERATION);
        speeds = new ArrayList<>(Constants.LOOPS_ACCELERATION);
        
        for (int i = 0; i < Constants.LOOPS_ACCELERATION; i++)
        {
            outputs.add(((Math.abs(random.nextInt()) % 21) - 10)/10.);
        }
        
        random.setSeed(0);
        for (int i = 0; i < Constants.LOOPS_ACCELERATION; i++)
        {
            speeds.add(0.);
        }
    
        for (int i = 0; i < Constants.LOOPS_ACCELERATION; i++)
        {
            speeds.set(Constants.LOOPS_ACCELERATION - 1 - i, getInstSpeed(random, outputs.get(i)));
        }
    }
    
    @Test
    public void getSpeedReturnsUpdatedValues()
    {
        double actualSpeed = 2*(1./(Constants.LOOPS_ACCELERATION + 1))*speeds.get(0);
        for(int i = 1; i < Constants.LOOPS_ACCELERATION; i++)
        {
            actualSpeed += (1./(Constants.LOOPS_ACCELERATION + 1))*speeds.get(i);
        }
    
        System.out.print("Sending motor outputs: [ ");
        for(int i = 0; i < Constants.LOOPS_ACCELERATION; i++)
        {
            System.out.printf("%1.1f ", outputs.get(i));
            motor.set(outputs.get(i));
            encoder.update();
        }
        System.out.printf("]\nExpecting speed %f\n", actualSpeed);
        assertThat(encoder.getSpeed(), is(actualSpeed));
    }
    
    @Test
    public void getPositionReturnsUpdatedValues()
    {
        int actualTicks = (int) (Constants.COUNTS_PER_REV*((2*(1./(Constants.LOOPS_ACCELERATION + 1))*speeds.get(Constants.LOOPS_ACCELERATION - 1))/ Constants.LOOPS_PER_SEC));
        double actualPos = (double)actualTicks/ Constants.COUNTS_PER_REV;
        motor.set(outputs.get(0));
        encoder.update();
        System.out.printf("Set output to %f, expecting position %f\n", outputs.get(0), actualPos);
    
        assertThat(encoder.getPosition(), is(actualPos));
    
        actualTicks += Constants.COUNTS_PER_REV*(2*(1./(Constants.LOOPS_ACCELERATION + 1))*speeds.get(Constants.LOOPS_ACCELERATION - 2) + (1./(Constants.LOOPS_ACCELERATION + 1))*speeds.get(Constants.LOOPS_ACCELERATION - 1))/ Constants.LOOPS_PER_SEC;
        actualPos = (double)actualTicks/ Constants.COUNTS_PER_REV;
        motor.set(outputs.get(1));
        encoder.update();
        System.out.printf("Set output to %f, expecting position %f\n", outputs.get(1), actualPos);
    
        assertThat(encoder.getPosition(), is(actualPos));
    }
    
    @Test
    public void getRawReturnsUpdatedValues()
    {
        int actualTicks = (int) (Constants.COUNTS_PER_REV*((2*(1./(Constants.LOOPS_ACCELERATION + 1))*speeds.get(Constants.LOOPS_ACCELERATION - 1))/ Constants.LOOPS_PER_SEC));
        motor.set(outputs.get(0));
        encoder.update();
        System.out.printf("Set output to %f, expecting count %d\n", outputs.get(0), actualTicks);
    
        assertThat(encoder.getRaw(), is(actualTicks));
    
        actualTicks += Constants.COUNTS_PER_REV*(2*(1./(Constants.LOOPS_ACCELERATION + 1))*speeds.get(Constants.LOOPS_ACCELERATION - 2) + (1./(Constants.LOOPS_ACCELERATION + 1))*speeds.get(Constants.LOOPS_ACCELERATION - 1))/ Constants.LOOPS_PER_SEC;
        motor.set(outputs.get(1));
        encoder.update();
        System.out.printf("Set output to %f, expecting position %d\n", outputs.get(1), actualTicks);
    
        assertThat(encoder.getRaw(), is(actualTicks));
    }
    
    @Test
    public void resetSetsPositionToZero()
    {
        motor.set(1);
        encoder.update();
        encoder.reset(false);
        
        assertThat("Raw count should be 0", encoder.getRaw(), is(0));
        assertThat("Position should be 0", encoder.getPosition(), is(0.));
    }
    
    @Test
    public void resetObeysSpeedFlag()
    {
        motor.set(1);
        encoder.update();
        encoder.reset(false);
    
        assertTrue("Reset position without resetting speed, expect speed greater than zero", encoder.getSpeed() > 0);
        
        encoder.reset(true);
        assertThat("Reset position and speed, expect zero speed", encoder.getSpeed(), is(0.));
    }
    
    @Test
    public void updateUsesCorrectAmountOfRandomness()
    {
        motor.set(1);
        encoder.update();
        
        double speed = 2*(1./(Constants.LOOPS_ACCELERATION + 1))*getInstSpeed(new Random(0), 1);
        System.out.printf("Output set to 1, expect speed %f\n", speed);
        assertThat(encoder.getSpeed(), is(speed));
    }
    
    double getInstSpeed(Random random, double output)
    {
        int noise = (int)(((Math.abs(random.nextInt()) % (2* Constants.ACCURACY_COUNTS + 1)) - Constants.ACCURACY_COUNTS)*output);
        return (output + (double)noise/ Constants.COUNTS_PER_REV)* Constants.LOOPS_PER_SEC;
    }
}
