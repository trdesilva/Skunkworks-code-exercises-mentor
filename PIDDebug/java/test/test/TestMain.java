package test;

import org.junit.runner.JUnitCore;
import org.junit.runner.Result;
import org.junit.runner.notification.Failure;
import test.BVT_PidController;

public class TestMain
{
    public static void main(String[] args) throws Throwable
    {
        boolean allPassed = runClass(UT_Motor.class);
        allPassed &= runClass(UT_Encoder.class);
        allPassed &= runClass(BVT_PidController.class);
        if(allPassed)
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
        System.out.println(classToRun.getSimpleName() + " passed: " + result.wasSuccessful());
        return result.wasSuccessful();
    }
}
