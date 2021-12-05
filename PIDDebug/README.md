# PID Debug

This project has a simulated motor, encoder, and PID controller, but at the moment, it's pretty broken. Your task is to get it back in working order and to get the tests to pass. Each of the three classes is updated at discrete timesteps, the length of which is defined in Constants. The Motor is a simple class; it's more or less a container for an output percentage (-1 to 1) that the Encoder can read from and the PIDController can write to. The Encoder is a bit more complex: it takes the current motor output, adds some random noise to it, and stores the expected speed value in a shift register. The expected speeds in the shift register are used to calculate a weighted rolling average over the last few ticks, which simulates the motor having inertia. The "actual" speed is then used to determine the change in position for the timestep. The PIDController (actually a PIDFController) acts as one would expect a PID controller to. It reads the relevant input value from the Encoder for the control mode it's in--position in rotations, position in ticks, or speed in rotations per second. It does the relevant math and sends the output to the Motor. If the PID is disabled, it sends the Motor a 0 for the output.

To run the tests in C++:

1. Compile the project by calling "make all" in a terminal (use Cygwin in Windows). This will compile and build the code into a shared library that the test executable links to.

    a. If you're on Linux, you'll need to set the library search path so the test executable can find your library. Run "source linux-lib-path.sh"; it should automatically set the path.

2. Run the tests executable to test your implementation.

    a. If you're on Windows, use tests.exe.

    b. If you're on Linux, use tests with no extension.

To run the tests in Java:
1. Compile your code into a JAR file by going to Build > Build Artifacts in IntelliJ and building PIDDebug:jar.
2. Drop the supplied PIDDebugTest.jar file into the same directory as PIDDebug.jar (should be out\artifacts\PIDDebug_jar on Windows).
3. Right-click on PIDDebugTest.jar in the Project view in IntelliJ and click "Run 'PIDDebugTest.jar'" in the dropdown.

Once the tests run successfully, you're done.

# Background

Before you can start, there are a few things you'll need to understand:

 * basic control flow and operations
 * pointers (for C++)
 * inheritance
 * for/while loops
 * PID control
 * shift registers/queues/ring buffers

If you don't understand any of these, ask a mentor, search the internet, or try a related exercise.

# Tips

You'll probably run into a lot of issues that you haven't seen before or don't remember. Don't be afraid to check Stack Overflow! Knowing how to find solutions that other people have already come up with is a valuable skill, and an important part of this exercise.

You should probably import this exercise into Eclipse for C++ or IntelliJ for Java so you can make use of their debuggers. Good use of the debugger goes a long way in troubleshooting.

# Extensions

1. Sometimes you may need a PID to handle an input range that wraps at the ends (for example, having the robot rotate to a certain angle using a gyro that only returns 0 to 360 degrees). Add a "continuous" mode for positions that handles this case.
2. Make the simulator multithreaded by making Encoder::update() and PIDController::update() run in their own threads. Encoder::update() should read off a queue of motor outputs and produce encoder data, and PIDController::update() should read off a queue of encoder data and produce motor outputs.

