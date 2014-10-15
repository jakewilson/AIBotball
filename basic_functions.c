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
 * Returns TRUE if the robot has reached the edge of the map, FALSE if not.
 * @return: TRUE if the robot has reached the edge of the map, FALSE if not.
 */
int onEdge() {
	return senseBrightness(LIGHT_SENSOR_R) == DARK && senseBrightness(LIGHT_SENSOR_L) == DARK;
}

/*
 * If any of the light sensors sense DARK, but not both, then
 * turn the robot in the opposite direction from the sensor to correct
 * its course
 */
void correctCourse() {
	if (senseBrightness(LIGHT_SENSOR_R) == DARK && senseBrightness(LIGHT_SENSOR_L) == LIGHT) {
		turn(LEFT, DEGREE_2_P_5);
	} else 
		if (senseBrightness(LIGHT_SENSOR_R) == LIGHT && senseBrightness(LIGHT_SENSOR_L) == DARK) {
			turn(RIGHT, DEGREE_2_P_5);
		}
}

/*
 * Moves the robot forward by n amount of cells at SPEED
 * @param n: the number of cells to move
 */
void move(int n) {
    mav(RIGHT_MOTOR, SPEED);
    mav(LEFT_MOTOR, SPEED);
	clear_motor_position_counter(RIGHT_MOTOR);
	while (get_motor_position_counter(RIGHT_MOTOR) > (n * CELL_SIZE)) {
		correctCourse();
		mav(RIGHT_MOTOR, SPEED);
		mav(LEFT_MOTOR, SPEED);
		msleep(100);
	}
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
 * Uses the light sensor on port p and returns whether it was light or dark.
 * Light is defined by: x < 900
 * Dark is defined by: x >= 900
 * @return LIGHT or DARK, depending on the sensor input.
 */
int senseBrightness(int p) {
	return analog10(p) > 900 ? DARK : LIGHT;
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
