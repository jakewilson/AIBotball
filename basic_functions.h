/*
 * Simple API for moving the robot, moving the robot diagonally, turning the robot,
 * and moving the servo forward and backwards.
 *
 * @author: Jake Wilson
 * @date: 10/12/2014
 */


/* Ports */
#define LEFT_MOTOR   3
#define RIGHT_MOTOR  1
#define SERVO_PORT   2

#define LIGHT_SENSOR_R 0
#define LIGHT_SENSOR_L 5

/* Speeds */
#define SPEED -700
#define TURN_SPEED -400

/* the time it takes to traverse one cell at speed 800 */
#define CELL_TIME 1100

#define CELL_SIZE -800

/* Turn degrees. Values are the number of seconds to turn */
#define DEGREE_90 1750
#define DEGREE_10 (DEGREE_90 / 10)
#define DEGREE_5 (DEGREE_10 / 2)
#define DEGREE_2_P_5 (DEGREE_5 / 2)
#define DEGREE_45 (DEGREE_90 / 2)
#define DEGREE_180 (DEGREE_90 * 2)

/* The amount to increase the servo position by */
#define SERVO_INC 250

/* The middle position of the servo */
#define SERVO_MIDDLE 1024

/* Turn directions */
#define LEFT  0
#define RIGHT 2

/* Light Sensor Values */
#define LIGHT 0
#define DARK 1

/* Boolean Values */
#define TRUE  1
#define FALSE 0

/* Color Values */
#define RED    0
#define GREEN  1
#define PURPLE 2
#define WHITE  3


/* Functions */
void move();
void moveDiagonally(int n);
void turn(int dir, int deg);
void servoForwards();
void servoBackward();
int senseBrightness();
int onEdge();
int getColor();
