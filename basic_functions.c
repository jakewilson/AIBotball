#include "basic_functions.h"
#include <math.h>

/*
 * Returns the color seen by the camera
 * @return: either RED, GREEN, PURPLE, or WHITE
 */
int getColor(){
   int numChannels = 4;
   int i;
	int maxSum = 0; 
	int maxIndex = -1;
	int objCount=-1;
	int sum=0;
	int counts[4]={0,0,0,0};
	int k;
	int j;
   
   while(maxIndex==-1){
			camera_update(); //intake color
			for(k=0;k<7;k++){
				for(i = 0; i < numChannels; i++)
				{
				
					if((objCount=get_object_count(i))>0)//if there is an object of that color seen
					{	
						for(j=0; j<objCount;j++){
						sum=get_object_area(i,j)+sum;
						}
				
						if(sum>maxSum){
							maxSum=sum;
							maxIndex=i;
						}
						sum=0;
					}
				}
				if(maxIndex>=0){
					counts[maxIndex]++;
				}
				maxSum = 0;
			}
			for(k=0;k<4;k++){
				if(maxSum<counts[k]){
					maxSum=counts[k];
					maxIndex=k;
				}
			}
			maxSum=0;
		}
		printf("The color is %d\n",maxIndex);
      return maxIndex;
   }

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
 * If both light sensors see DARK and they still see DARK 50 ms later, then we're on the edge.
 * @return: TRUE if the robot has reached the edge of the map, FALSE if not.
 */
int onEdge() {
	if (senseBrightness(LIGHT_SENSOR_R) == DARK && senseBrightness(LIGHT_SENSOR_L) == DARK) {
		msleep(35);
		return senseBrightness(LIGHT_SENSOR_R) == DARK && senseBrightness(LIGHT_SENSOR_L) == DARK;
	}
	return FALSE;
}

/*
 * If any of the light sensors sense DARK, but not both, then
 * turn the robot in the opposite direction from the sensor to correct
 * its course
 */
void correctCourse() {
	if (senseBrightness(LIGHT_SENSOR_R) == DARK && senseBrightness(LIGHT_SENSOR_L) == LIGHT) {
		turn(LEFT, DEGREE_5);
	} else 
		if (senseBrightness(LIGHT_SENSOR_R) == LIGHT && senseBrightness(LIGHT_SENSOR_L) == DARK) {
			turn(RIGHT, DEGREE_5);
		}
}

/*
 * Moves the robot forward by n amount of cells at SPEED
 * @param n: the number of cells to move
 */
void move() {
    mav(RIGHT_MOTOR, SPEED);
    mav(LEFT_MOTOR, SPEED);
	clear_motor_position_counter(RIGHT_MOTOR);
	int time = 0;
	while (time < CELL_TIME) {
		correctCourse();
		mav(RIGHT_MOTOR, SPEED);
		mav(LEFT_MOTOR, SPEED);
		msleep(150);
		time += 150;
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
