#ifndef CONSTANTS_H
#define CONSTANTS_H 1

// Encoder
// Number of encoder ticks per revolution
#define COUNTS_PER_REV 1024
// Maximum error/inconsistency of encoder measurements in ticks per program loop
#define ACCURACY_COUNTS 0
// Program loops per second
#define LOOPS_PER_SEC 50
// Number of loops of history to account for in simulating the motor's speed
#define LOOPS_ACCELERATION 5

// PID config
// Number of revolutions we can be off from the setpoint to call it "good enough"
#define POSITION_REV_TOLERANCE .01
// Same as above, but ticks
#define POSITION_RAW_TOLERANCE POSITION_REV_TOLERANCE*COUNTS_PER_REV
// Same as above, but revolutions per second
#define SPEED_TOLERANCE .5

#endif
