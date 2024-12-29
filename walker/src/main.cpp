/*
a siple test program for my robot Setup written with c++ and PlatformIo
there are No Competible Motor Driver Pins or general PWM pins to power the Motors of my Robot
=> The RObot Setup Doesn't Work

LICENCE: GPL4
written by Ztirom45
*/

/*
#include <motors.hpp>

#include <Arduino.h>
#include <log.hpp>

#include <Adafruit_ADXL345_U.h>
#include <Vector.h>

#include <commands.hpp>
#include <sensors.hpp>


void wait_for_wifi_connection(){
  char recived = '7';
  bool loop = true;
  while(loop){
    loop = false;
    for(int i=0;i<30;i++){
      recived = Serial3.read();
      mylog(recived);
      if (recived=='7'||recived=='4'){
	loop = true;
      }
      delay(100);
    }
  }
  mylog("connected to WiFi");
}
String recived;
void setup(){	
	//Serial.begin(9600);	
	debug_init();
	mylog("Start");
	//setup motors
	//attachInterrupt(Encoder_1.getIntNum(), isr_process_encoder1, RISING);
	//attachInterrupt(Encoder_1.getIntNum(), isr_process_encoder1, RISING);
	//setup for encoder, does not work anyways
	//use with: runSpeed
	init_encoder();
	init_sensors();
	
	//setup wifimod
	//Serial3.begin(115200);
	//wait_for_wifi_connection();
	
	//setup commands	
	recived.reserve(MAX_COMMAND_LEN);
	parse_and_execute_action("forward_gyro 70");//debug rm later
}


String read_message(){
	if(Serial3.available()<=0){

	  return "";
	}
	recived = Serial3.readString();
	
	if(recived.substring(0,2)!="-m"){
	  return "";
	}
	return recived.substring(2,recived.indexOf("-e"));
}


float x_rot = 0;
void loop(){ 
  mylog("encoder");
  Encoder_1.loop();
  Encoder_2.loop();
  

  mylog("gyro");
  gyro.update();

  mylog("parse");
  parse_and_execute_action("");//read_message()); 

  //mylog(micros() - start);
  //debuging stuff
  /*if(Serial3.available()>0){
      Serial.print((char)Serial3.read());
  }*/
/*	
}*/
#include <Arduino.h>
void setup(){}
void loop(){}

