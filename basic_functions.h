/*
 * Simple API for moving the robot, moving the robot diagonally, turning the robot,
 * and moving the servo forward and backwards.
 */


/* Ports */
#define LEFT_MOTOR   3
#define RIGHT_MOTOR  1
#define SERVO_PORT   2
#define LIGHT_SENSOR 5

#define SPEED -800
#define TURN_SPEED -400

/* the time it takes to traverse one cell at speed SPEED */
#define CELL_TIME 1100

/* Turn degrees. Values are the number of seconds to turn*/
#define DEGREE_90 1850
#define DEGREE_45 (DEGREE_90 / 2)
#define DEGREE_180 (DEGREE_90 * 2)

/* The amount to increase the servo position by */
#define SERVO_INC 250

/* Turn directions */
#define LEFT  0
#define RIGHT 2

/* Light Sensor Values */
#define LIGHT 0
#define DARK 1

void move(int n);
void moveDiagonally(int n);
void turn(int dir, int deg);
void servoForwards();
void servoBackward();
int senseBrightness();

