import org.junit.Before;
import org.junit.Test;

import static org.hamcrest.CoreMatchers.is;
import static org.hamcrest.MatcherAssert.assertThat;

public class UT_Motor
{
    private Motor motor;
    
    @Before
    public void setup()
    {
        motor = new Motor(0);
    }
    
    @Test
    public void setChangesOutput()
    {
        System.out.println("Setting output to 0.5");
        motor.set(0.5);
        assertThat("Motor output should be 0.5", motor.getOutput(), is(0.5));
    
        System.out.println("Setting output to -0.5");
        motor.set(-0.5);
        assertThat("Motor output should be -0.5", motor.getOutput(), is(-0.5));
    }
    
    @Test
    public void setCannotIncreaseOutputBeyondMax()
    {
        System.out.println("Setting output to 10");
        motor.set(10);
        assertThat("Motor output should be 1", motor.getOutput(), is(1.));
    
        System.out.println("Setting output to -10");
        motor.set(-10);
        assertThat("Motor output should be -1", motor.getOutput(), is(-1.));
    }
}
