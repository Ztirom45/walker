
#include <sensors.hpp>


Adafruit_ADXL345_Unified acc = Adafruit_ADXL345_Unified(12345);
Adafruit_ADXL345_Unified acc2 = Adafruit_ADXL345_Unified(12344);
Adafruit_MPU6050 mpu;

double ultrasonic_cm(int trig_pin,int echo_pin,double conversion_factor){
  //trigger
  pinMode(trig_pin, OUTPUT);
  digitalWrite(trig_pin,LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin,LOW);

  //read
  pinMode(echo_pin,INPUT);
  return (double)pulseIn(echo_pin,HIGH) *conversion_factor;
}


void init_sensors(){
	//setup sensors
	if(!acc.begin(0x53))
	{
	  Serial.println("no ADXL345 on53d detected ... Check your wiring!");
	  while(1);
	}
	if(!acc2.begin(0x1d))
	{
	  Serial.println("no ADXL345 on 0x1d detected ... Check your wiring!");
	  while(1);
	}
	acc.setRange(ADXL345_RANGE_16_G);
	acc2.setRange(ADXL345_RANGE_16_G);
	
	if (!mpu.begin()) {
	  Serial.println("Failed to find MPU6050 chip");
	  while(1);
	}
}
