/*
this is the library for all commands that can be send via mqtt
TODO smartpointer
*/

#pragma once


#include <Arduino.h>
#include <log.hpp>
#include <Adafruit_ADXL345_U.h>
#include <Vector.h>
#include <motors.hpp>
#include <sensors.hpp>

#define MAX_COMMAND_LEN 50


struct Command{
	String command;
	void (*setup)(Vector<String>,Command*);
	void (*loop)(Command*);
	int speed;//for looped motor functions
	Command(
		String command,
		void (*setup)(Vector<String>,Command*),
		void (*loop)(Command *command)
	);
	
	
};

//void init_commands(*MeEcoderOnBoard Encoder_1,*MeEcoderOnBoard Encoder_2);

void forward_setup(Vector<String> args,Command *command);
void forward_loop(Command *command);

void stop_setup(Vector<String> args,Command *command);
void stop_loop(Command *command);

void motor_right_setup(Vector<String> args,Command *command);
void motor_right_loop(Command *command);

void motor_left_setup(Vector<String> args,Command *command);
void motor_left_loop(Command *command);

void turn_setup(Vector<String> args,Command *command);
void turn_loop(Command *command);

#define STEARING_FAKTOR 2
void follow_wall_setup(Vector<String> args,Command *command);
void follow_wall_loop(Command *command);

#ifdef LEG_TRACKING_ENABLET
void forward_legwise_setup(Vector<String> args,Command *command);
void forward_legwise_loop(Command *command);
//require functions:
void leg1_move(int speed,int direction);
void leg2_move(int speed,int direction);
#endif

void forward_gyro_setup(Vector<String> args,Command *command);
void forward_gyro_loop(Command *command);

#ifdef LEG_TRACKING_ENABLET
#define COMMAND_COUNT 8
#else
#define COMMAND_COUNT 7
#endif

extern Command commands[COMMAND_COUNT];

void parse_and_execute_action(String action);
	
