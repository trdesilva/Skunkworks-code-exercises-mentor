package src;

public class Motor implements Outputable
{
    private int port;
    private double output;
    
    public Motor(int port)
    {
        this.port = port;
    }
    
    /**
     * Set the motor's output. Capped to the range [-1, 1].
     */
    @Override
    public void set(double output)
    {
        if(output > 1) output = 1;
        if(output < -1) output = -1;
        this.output = output;
    }
    
    /**
     * Returns which port this motor is plugged in to.
     */
    public int getPort()
    {
        return port;
    }
    
    /**
     * Returns the motor's current output setting.
     */
    public double getOutput()
    {
        return output;
    }
}
