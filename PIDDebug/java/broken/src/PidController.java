package src;

public class PidController
{
    public enum Mode
    {
        POSITION_RAW;
        POSITION_REV;
        SPEED;
    }
    
    private Outputable outputable;
    private Encoder encoder;
    private Mode mode;
    
    private double p;
    private double i;
    private double d;
    private double f;
    
    private double setpoint;
    private boolean enabled;
    private double lastError;
    private double sumError;
    
    public PidController(Outputable outputable, Encoder encoder, Mode mode, double p, double i, double d)
    {
        this(outputable, encoder, mode, p, i, d, 0);
    }
    
    public PidController(Outputable outputable, Encoder encoder, Mode mode, double p, double i, double d, double f)
    {
        this.outputable = outputable;
        this.encoder = new Encoder(encoder);
        this.mode = mode;
        this.p = p;
        this.i = i;
        this.d = d;
        this.f = f;
        
        setpoint = 0;
        enabled = false;
        lastError = 0;
        sumError = 0;
    }
    
    /**
     * Advance the PID controller by one time step. Updates the encoder reading and sets the motor output appropriately.
     */
    public void update()
    {
        if(enabled)
        {
            encoder.update();
        
            double output = 0;
            double curr;
            if(mode == Mode.POSITION_RAW)
            {
                curr = encoder.getRaw();
            }
            else
            {
                curr = encoder.getSpeed();
            }
            double error = curr - setpoint;
            double diffError = lastError - error;
        
            sumError += error;
            output = p * error + (i * sumError) / Constants.LOOPS_PER_SEC + (d * diffError) / Constants.LOOPS_PER_SEC + f * setpoint;
            lastError = error;
        
            outputable.set(output);
        }
        else
        {
            outputable.set(0);
        }
    }
    
    /**
     * Resets the setpoint and stored error data, and disables the PID.
     */
    public void reset()
    {
        setpoint = 0;
        lastError = 0;
        disable();
    }
    
    /**
     * Enables the PID. Prevents the control mode from being changed.
     */
    public void enable()
    {
        enabled = true;
    }
    
    /**
     * Disables the PID.
     */
    public void disable()
    {
        enabled = false;
        outputable.set(0);
    }
    
    /**
     * Sets the setpoint.
     */
    public void setSetpoint(double setpoint)
    {
        this.setpoint = setpoint;
    }
    
    /**
     * Update the values of P, I, D, and F. F defaults to 0.
     */
    public void setConstants(double p, double i, double d)
    {
        setConstants(p, i, d, 0);
    }
    
    
    public void setConstants(double p, double i, double d, double f)
    {
        this.p = p;
        this.i = i;
        this.d = d;
        this.f = f;
    }
    
    /**
     * Update the control mode. This changes the value that the PIDController reads from the Encoder in update(). The options are
     * POSITION_RAW, POSITION_REV, and SPEED.
     */
    public void setMode(Mode mode)
    {
        this.mode = mode;
    }
    
    /**
     * Returns true if the encoder's current state is within an acceptable error margin of the setpoint.
     */
    public boolean onTarget()
    {
        if(mode == Mode.POSITION_RAW)
        {
            return Math.abs(encoder.getRaw() - setpoint) > Constants.POSITION_RAW_TOLERANCE;
        }
        else
        {
            return Math.abs(encoder.getSpeed() - setpoint) > Constants.SPEED_TOLERANCE;
        }
    }
    
    public Mode getMode()
    {
        return mode;
    }
}
