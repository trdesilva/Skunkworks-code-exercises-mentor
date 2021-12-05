package src;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class Encoder
{
    private static Random rand = new Random();
    
    private Motor motor;
    private int count;
    private List<Double> speed;
    
    public Encoder(Outputable outputable)
    {
        this.motor = outputable;
        
        count = 0;
        speed = new ArrayList<>(Constants.LOOPS_ACCELERATION);
        Constants.ACCURACY_COUNTS = 0; // TODO this is for testing, remember to fix this
    }
    
    public Encoder(Encoder other)
    {
        this.motor = other.getMotor();
        
        count = 0;
        speed = new ArrayList<>(Constants.LOOPS_ACCELERATION);
    }
    
    /**
     * Reset the encoder's position to 0.
     */
    public void reset(boolean resetSpeed)
    {
        count = 0;
        if(resetSpeed)
        {
            for(int i = 0; i < Constants.LOOPS_ACCELERATION; i++)
            {
                speed.set(i, 0.);
            }
        }
    }
    
    /**
     * Advances the encoder data by one time step. Uses a shift register of motor outputs to simluate non-instantaneous
     * speed changes.
     */
    public void update()
    {
        double output = motor.getOutput();
        // add pseudorandom noise from -20 to 20 scaling with output
        int noise = (((Math.abs(rand.nextInt()) % (2 * Constants.ACCURACY_COUNTS + 1)) - Constants.ACCURACY_COUNTS) * output);
    
        int i = 0;
        while(i++ != Constants.LOOPS_ACCELERATION - 1)
        {
            // starting with the second-to-last entry, shift each entry to the right by 1 (last entry gets dropped)
            speed.set(Constants.LOOPS_ACCELERATION - i, speed.get(Constants.LOOPS_ACCELERATION - i - 1));
            i++;
        }
        speed.set(0, (output + (double)noise / Constants.COUNTS_PER_REV) * Constants.LOOPS_PER_SEC);
    
        count += Constants.COUNTS_PER_REV*getSpeed();
    }
    
    public void setRandSeed(int seed)
    {
        rand.setSeed(seed);
    }
    
    public int getRaw()
    {
        return count;
    }
    
    public double getPosition()
    {
        return ((double)count)/ Constants.COUNTS_PER_REV;
    }
    
    public double getSpeed()
    {
        double weight = 1./(Constants.LOOPS_ACCELERATION + 1);
        double average = 2*weight*speed.get(0);
        for(int i = 1; i < Constants.LOOPS_ACCELERATION; i++)
        {
            average += weight*speed.get(i);
        }
        return average;
    }
    
    public Motor getMotor()
    {
        return motor;
    }
}
