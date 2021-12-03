package test;

import org.junit.runner.JUnitCore;
import org.junit.runner.Result;
import org.junit.runner.notification.Failure;
import test.BVT_PidController;

public class TestMain
{
    public static void main(String[] args) throws Throwable
    {
        if(runClass(UT_Motor.class) &&
                runClass(UT_Encoder.class) &&
                runClass(BVT_PidController.class))
        {
            System.out.println("All tests pass!");
        }
        else
        {
            System.out.println("Test failure reported; see above.");
        }
    }
    
    private static boolean runClass(Class classToRun)
    {
        Result result = JUnitCore.runClasses(classToRun);
        for(final Failure failure : result.getFailures())
        {
            System.out.println(failure.toString());
        }
        System.out.println(classToRun.toString() + " passed: " + result.wasSuccessful());
        return result.wasSuccessful();
    }
}
