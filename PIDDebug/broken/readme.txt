INTRODUCTION

This project has a simulated motor, encoder, and PID controller, but at the moment, it's pretty broken. Your task is to get it back in working order and to get the tests to pass. To run the tests:
1. Compile the project by calling "make all" in a terminal (use Cygwin in Windows). This will compile and build the code into a shared library that the test executable links to.
1a. If you're on Linux, you'll need to set the library search path so the test executable can find your library. Run "source linux-lib-path.sh"; it should automatically set the path.
2a. If you're on Windows, run tests.exe to test your implementation.
2b. If you're on Linux, run tests with no extension.
Once the tests run successfully, you're done.

BACKGROUND

Before you can start, there are a few things you'll need to understand:
-Basic control flow and operations
-Pointers
-For/while loops
-PID control
-Shift registers/queues

If you don't understand and of these, ask a mentor or search the internet. You'll probably run into a lot of issues that you haven't seen before or don't remember. Don't be afraid to check Stack Overflow! Knowing how to find solutions that other people have already come up with is a valuable skill, and an important part of this exercise.

HOW IT SHOULD WORK

Each of the three classes is updated at discrete timesteps, the length of which is defined in Constants.
The Motor is a simple class. It's more or less a container for an output percentage (-1 to 1) that the Encoder can read from and the PIDController can write to.
The Encoder is a bit more complex: it takes the current motor output, adds a bit of random noise to it, and stores the expected speed value in a shift register. The expected speeds in the shift register are used to calculate a weighted rolling average over the last few ticks, which simulates the motor having inertia. The "actual" speed is then used to determine the change in position for the timestep.
The PIDController (actually a PIDFController) acts as one would expect a PID controller to. It reads the relevant input value from the Encoder for the control mode it's in--position in rotations, position in ticks, or speed in rotations per second. It does the relevant math and sends the output to the Motor. If the PID is disabled, it sends the Motor a 0 for the output.

There are a lot of errors, but all of them are solvable, and the end result is a useful tool. Good luck!
