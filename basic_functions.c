#include "basic_functions.h"
#include <math.h>

/*
 * Moves the servo backward(s)
 */
void servoBackwards() {
    set_servo_position(SERVO_PORT, get_servo_position(SERVO_PORT) - SERVO_INC);
}

/*
 * Moves the servo forward(s)
 */
void servoForwards() {
    set_servo_position(SERVO_PORT, get_servo_position(SERVO_PORT) + SERVO_INC);
}

/*
 * Moves the robot forward by n amount of cells at SPEED
 * @param n: the number of cells to move
 */
void move(int n) {
    mav(RIGHT_MOTOR, SPEED);
    mav(LEFT_MOTOR, SPEED);
    msleep(n * CELL_TIME);
}

/*
 * Moves the robot backwards by n amount of cells at SPEED
 * @param n: the number of cells to move
 */
void moveBackwards(int n) {
	mav(RIGHT_MOTOR, -SPEED);
	mav(LEFT_MOTOR, -SPEED);
	msleep(n * CELL_TIME);
}

/*
 * Moves the robot forward by n amount of cells at SPEED
 * @param n: the number of cells to move
 */
void moveDiagonally(int n) {
    mav(RIGHT_MOTOR, SPEED);
    mav(LEFT_MOTOR, SPEED);
    msleep(n * sqrt((CELL_TIME * CELL_TIME) + (CELL_TIME * CELL_TIME)));
}

/*
 * Uses the light sensor on port LIGHT_SENSOR and returns whether it was light or dark.
 * Light is defined by: x < 980
 * Dark is defined by: x >= 980
 * @return LIGHT or DARK, depending on the sensor input.
 */
int senseBrightness() {
	return analog10(LIGHT_SENSOR) > 980 ? DARK : LIGHT;
}

/*
 * Stops the motor opposite to the direction to turn, then turns it back
 * to full speed
 * @param dir: the direction in which to turn the robot - use macros LEFT or RIGHT
 * @param deg: the degree in which to turn the robot. Possible args include:
 * DEGREE_90, DEGREE_45, DEGREE_180.
 */
void turn(int dir, int deg) {
    int motor = dir == LEFT ? LEFT_MOTOR : RIGHT_MOTOR;
    clear_motor_position_counter(motor);
    mav(dir == LEFT ? LEFT_MOTOR : RIGHT_MOTOR, -TURN_SPEED);
    mav(dir == LEFT ? RIGHT_MOTOR : LEFT_MOTOR, TURN_SPEED);
    msleep(deg);
}
