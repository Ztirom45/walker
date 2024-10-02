#include "HardwareSerial.h"
#include <commands.hpp>

Command::Command(String command,
		void (*setup)(Vector<String>),
		void (*loop)(),
		int argc
):command(command),setup(setup),loop(loop),argc(argc){

}



void forward_setup(Vector<String> args){
      if(args.size() != 1){
	Serial.print("forward(speed) expected 1 argument, but ");
	Serial.print(args.size());
	Serial.println(" were given");
	return;
      }
      Encoder_1.setTarPWM(args[0].toInt());
      Encoder_2.setTarPWM(-(args[0].toInt()));
      Serial.print("driving forward with speed: ");
      Serial.println(args[0]);
}
void forward_loop(){}

void stop_setup(Vector<String> args){
      if(args.size() != 0){
	Serial.print("stop() expected o argument, but ");
	Serial.print(args.size());
	Serial.println(" were given");
	return;
      }
      Encoder_1.setTarPWM(0);
      Encoder_2.setTarPWM(0);
      Serial.print("stopped");
}
void stop_loop(){}

void motor_right_setup(Vector<String> args){
      if(args.size() != 1){
	Serial.print("error motorRight(speed) expected 1 argument, but ");
	Serial.print(args.size());
	Serial.println(" were given");
	return;
      }
      Encoder_1.setTarPWM(args[0].toInt());
      Serial.print("driving forward with speed: ");
      Serial.println(args[0]);
}
void motor_right_loop(){}

void motor_left_setup(Vector<String> args){
      if(args.size() != 1){
	Serial.print("error motorLeft(speed) expected 1 argument, but ");
	Serial.print(args.size());
	Serial.println(" were given");
	return;
      }
      Encoder_2.setTarPWM(-args[0].toInt());
      Serial.print("driving forward with speed: ");
      Serial.println(args[0]);
}

void motor_left_loop(){}

void turn_setup(Vector<String> args){
      if(args.size() != 1){
	Serial.print("error turn(speed) requires 1 argument, but ");
	Serial.print(args.size());
	Serial.println(" were given");
	return;
      }
      Encoder_1.setTarPWM(args[0].toInt());
      Encoder_2.setTarPWM(args[0].toInt());
      Serial.print("turning right Motor with speed: ");
      Serial.println(args[0]);
}
void turn_loop(){}

void follow_wall_setup(Vector<String> args){
      if(args.size() != 0){
	Serial.print("error: follow_wall() requires 0 argument, but ");
	Serial.print(args.size());
	Serial.println(" were given");
	return;
      } 
      Serial.println("following wall");
}

void follow_wall_loop(){
	float u1 = 0;//read_ultrasonic1();
	float u2 = 0;//read_ultrasonic2();
	float us_div = u1-u2;
	Serial.print(" 1:");
	Serial.print(u1);
	Serial.print(" 2:");
	Serial.print(u2);
	Serial.print(" div:");
	Serial.println(us_div*STEARING_FAKTOR);
	Encoder_1.setTarPWM(-100-us_div*STEARING_FAKTOR);
	Encoder_2.setTarPWM(100+us_div*STEARING_FAKTOR);
	Encoder_1.loop();
	Encoder_2.loop();
	
}
/*
void init_commands(*MeEncoderOnBoard Encoder_1,*MeEcoderOnBoard Encoder_2){
  Serial.println("hello");

};*/

Command array_initilizer[COMMAND_COUNT] ={
	Command("forward",&forward_setup,&forward_loop,1),    
	Command("stop",&stop_setup,&stop_loop,0),
	Command("motorRight",&motor_right_setup,&motor_right_loop,1),
	Command("motorLeft",&motor_left_setup,&motor_left_loop,1),
	Command("turn",&turn_setup,&turn_loop,1),
	Command("follow_wall",&follow_wall_setup,&follow_wall_loop,0),
};
