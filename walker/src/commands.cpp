#include <commands.hpp>

void forward_setup(){}
void forward_loop(){}

void stop_setup(){}
void stop_loop(){}

void motor_right_setup(){}
void motor_right_loop(){}

void motor_left_setup(){}
void motor_left_loop(){}

void turn_setup(){}
void turn_loop(){}

void follow_wall_setup(){}
void follow_wall_loop(){}

void init_commands(){
  Serial.println("hello");
}

command array_initilizer[COMMAND_COUNT] ={
	{"forwart",&forward_setup,&forward_loop,1},
	    
	{"stop",&stop_setup,&stop_loop,0},
	{"motorRight",&motor_right_setup,&motor_right_loop,1},
	{"motorLeft",&motor_left_setup,&motor_left_loop,1},
	{"turn",&turn_setup,&turn_loop,1},
	{"follow_wall",&follow_wall_setup,&follow_wall_loop,0},
};
