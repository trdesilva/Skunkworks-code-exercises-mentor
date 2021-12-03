package src;

public class Main
{
    public static void main(String[] args)
    {
        Motor motor = new Motor(0);
        Encoder encoder = new Encoder(motor);
        PidController pidController = new PidController(motor, encoder, PidController.Mode.POSITION_REV, 1, 0, 0);
        pidController.setSetpoint(10);
        pidController.enable();
    
        Motor motor2 = new Motor(1);
        Encoder encoder2 = new Encoder(motor2);
        PidController pidController2 = new PidController(motor2, encoder2, PidController.Mode.SPEED, 0, 0, 0, .4/20);
        pidController2.setSetpoint(20);
        pidController2.enable();
    
        int ticks = 0;
    
        while(!pidController.onTarget())
        {
            pidController.update();
            pidController2.update();
            System.out.println(String.format("tick:\t%d\tcurrent position:\t%f\tcurrent speed:\t%f", ++ticks, encoder.getPosition(), encoder.getSpeed()));
            System.out.println(String.format("tick:\t%d\tcurrent speed:\t%f", ticks, encoder2.getSpeed()));
        }
    
        System.out.println(String.format("done with position %f", encoder.getPosition()));
    }
}
