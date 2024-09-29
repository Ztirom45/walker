#include <commands.hpp>


void forward_setup(Vector<String> args){
      //Encoder_1.setTarPWM(args[0].toInt());
      //Encoder_2.setTarPWM(-(args[0].toInt()));
      Serial.print("driving forward with speed: ");
      Serial.println(args[0]);
}

Command::Command(String command,
		void (*setup)(Vector<String>),
		void (*loop)(),
		int argc
):command(command),setup(setup),loop(loop),argc(argc){

}


void forward_loop(){}

void stop_setup(Vector<String> args){}
void stop_loop(){}

void motor_right_setup(Vector<String>){}
void motor_right_loop(){}

void motor_left_setup(Vector<String>){}
void motor_left_loop(){}

void turn_setup(Vector<String>){}
void turn_loop(){}

void follow_wall_setup(Vector<String>){}
void follow_wall_loop(){}
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
