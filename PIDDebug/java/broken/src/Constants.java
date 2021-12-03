package src;

public class Constants
{
    public static int COUNTS_PER_REV = 1024;
    public static int ACCURACY_COUNTS = 20;
    public static int LOOPS_PER_SEC = 50;
    public static int LOOPS_ACCELERATION = 5;
    
    public static double POSITION_REV_TOLERANCE = .01;
    public static double POSITION_RAW_TOLERANCE = POSITION_REV_TOLERANCE*COUNTS_PER_REV;
    public static double SPEED_TOLERANCE = .5;
}
