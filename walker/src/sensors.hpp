#pragma once

#include <HardwareSerial.h>
#include <Arduino.h>
#include <Adafruit_ADXL345_U.h>
#include <Vector.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

//uncomment if you want to enable forward_legwise
//WARNING: LEG_TRACKING ist experimental and does not necessarily work
//#define LEG_TRACKING_ENABLET

double ultrasonic_cm(int trig_pin,int echo_pin,double conversion_factor);

#define read_ultrasonic1() ultrasonic_cm(28,30,0.034 / 2.0)
#define read_ultrasonic2() ultrasonic_cm(29,39,0.034 / 2.0)

void init_sensors();

#ifdef LEG_TRACKING_ENABLET
	extern Adafruit_ADXL345_Unified acc;
	extern Adafruit_ADXL345_Unified acc2;
#endif
struct Gyro{
	Adafruit_MPU6050 mpu;
	float gyro_x;
	float gyro_y;
	float gyro_z;
	void init();
	void update();
};


extern Gyro gyro;

