/*
this is the library for all commands that can be send via mqtt
TODO smartpointer
*/

#pragma once


#include <MeEncoderNew.h>
#include <HardwareSerial.h>
#include <Arduino.h>
#include <Adafruit_ADXL345_U.h>
#include <Vector.h>
#define MAX_COMMAND_LEN 50


struct command{
	String command;
	void (*setup)();
	void (*loop)();
	int args;
};

void init_commands();

void forward_setup(int speed);
void forward_loop();

void stop_setup();
void stop_loop();

void motor_right_setup(int speed);
void motor_right_loop();

void motor_left_setup(int speed);
void motor_left_loop();

void turn_setup(int speed);
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
