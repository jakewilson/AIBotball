#include "basic_functions.h"

/*
 * First challenge in the botball tournament round 2
 */
int main() {
	enable_servos();
	set_servo_position(SERVO_PORT, 1024); // set servo in the middle
	move(1);
	servoForwards();
	turn(RIGHT, DEGREE_45);
	moveDiagonally(2);
	servoForwards();
	moveDiagonally(1);
	ao();
	return 0;
}
