package test;

import org.junit.runner.JUnitCore;
import org.junit.runner.Result;
import org.junit.runner.notification.Failure;

public class TestMain
{
    public static void main(String[] args) throws Throwable
    {
        runClass(UT_Motor.class);
        runClass(UT_Encoder.class);
        runClass(BVT_PidController.class);
    }
    
    private static void runClass(Class classToRun)
    {
        Result result = JUnitCore.runClasses(classToRun);
        for (final Failure failure : result.getFailures())
        {
            System.out.println(failure.toString());
        }
        System.out.println(result.wasSuccessful());
    }
}
