/*
this is the library for all commands that can be send via mqtt
TODO smartpointer
*/

#pragma once


#include <HardwareSerial.h>
#include <Arduino.h>
#include <Adafruit_ADXL345_U.h>
#include <Vector.h>
//#include <motors.hpp>
//#include <MeMegaPi.h>

#define MAX_COMMAND_LEN 50


struct Command{
	String command;
	void (*setup)(Vector<String>);
	void (*loop)();
	int argc;
	Command(
		String command,
		void (*setup)(Vector<String>),
		void (*loop)(),
		int argc
	);
	
	
};

//void init_commands(*MeEcoderOnBoard Encoder_1,*MeEcoderOnBoard Encoder_2);

void forward_setup(Vector<String> args);
void forward_loop();

void stop_setup(Vector<String> args);
void stop_loop();

void motor_right_setup(Vector<String> args);
void motor_right_loop();

void motor_left_setup(Vector<String> args);
void motor_left_loop();

void turn_setup(Vector<String> args);
void turn_loop();

void follow_wall_setup();
void follow_wall_loop();
/*
void _setup();
void _loop();
*/
#define COMMAND_COUNT 6

//Vector<command> commands = Vector(array_initilizer);
//command array_initilizer;
