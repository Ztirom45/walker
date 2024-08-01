/*
a siple test program for my robot Setup written with c++ and PlatformIo
there are No Competible Motor Driver Pins or general PWM pins to power the Motors of my Robot
=> The RObot Setup Doesn't Work

LICENCE: GPL4
written by Ztirom45
*/

#define MAX_COMMAND_LEN 50

#include <HardwareSerial.h>
#include <MeEncoderNew.h>
#include <Arduino.h>
#include <MeMegaPi.h>
#include <Vector.h>

MeEncoderOnBoard Encoder_1(SLOT1);
MeEncoderOnBoard Encoder_2(SLOT2);
MeEncoderOnBoard Encoder_3(SLOT3);
MeEncoderOnBoard Encoder_4(SLOT4);

void isr_process_encoder1(void){
  if(digitalRead(Encoder_1.getPortB()) == 0){
    Encoder_1.pulsePosMinus();
  }else{
    Encoder_1.pulsePosPlus();
  }
}
void isr_process_encoder2(void){
  if(digitalRead(Encoder_2.getPortB()) == 0){
    Encoder_2.pulsePosMinus();
  }else{
    Encoder_2.pulsePosPlus();
  }
}

void wait_for_wifi_connection(){
  char recived = '7';
  bool loop = true;
  while(loop){
    loop = false;
    for(int i=0;i<30;i++){
      recived = Serial3.read();
      Serial.println(recived);
      if (recived=='7'||recived=='4'){
	loop = true;
      }
      delay(100);
    }
  }
  Serial.println("connected to WiFi");
}

void setup(){	
	Serial.begin(9600);
	Serial.println("Start");
	Serial3.begin(115200);
	attachInterrupt(Encoder_1.getIntNum(), isr_process_encoder1, RISING);
	attachInterrupt(Encoder_1.getIntNum(), isr_process_encoder1, RISING);
	Encoder_1.setTarPWM(0);
	Encoder_2.setTarPWM(0);
	wait_for_wifi_connection();
}

//do not write "data:" as topic or "/////" as message or topic
String read_message(){
	if(Serial3.available()>0){
	  return "";
	}	
	String recived = Serial3.readString();
	if(recived.substring(0,15)!=String("--new message--")){
	  return "";
	}
	return recived.substring(recived.indexOf("data:")+5,recived.indexOf("\n--end of message--"));
}

void parse_and_execute_action(String action){
    if(action == ""){
      return;
    }
    Serial.println(action);
    int pos = 0;
    String storage_array[MAX_COMMAND_LEN];
    Vector<String> args(storage_array);
    
    pos = action.lastIndexOf(" ");
    
    action.remove(action.length()-2, action.length());//remove \n
    while (pos != -1) {//separates string in reverse order and pushes to args
        String token = action.substring(pos, action.length());
        args.push_back(token);
        action.remove(pos, pos + token.length());
	pos = action.lastIndexOf(" ");
    }
    String command = action;//the part wich stays after the loop is the command
    if(command == "forward"){
      if(args.size() != 1){
	Serial.print("error forward(speed) requires 1 argument, but ");
	Serial.print(args.size());
	Serial.println(" were given");
	return;
      }
      Encoder_1.setTarPWM(args[0].toInt());
      Encoder_2.setTarPWM(-(args[0].toInt()));
      Serial.print("driving forward with speed: ");
      Serial.println(args[0]);
      return;
    }
    if(command == "stop"){
      if(args.size() != 0){
	Serial.print("error forward(speed) requires 0 argument, but ");
	Serial.print(args.size());
	Serial.println(" were given");
	return;
      }
      Encoder_1.setTarPWM(0);
      Encoder_2.setTarPWM(0);
      Serial.print("stops motors");
      return;
    }
    if(command == "motorLeft"){
      if(args.size() != 1){
	Serial.print("error motorLeft(speed) requires 1 argument, but ");
	Serial.print(args.size());
	Serial.println(" were given");
	return;
      }
      Encoder_2.setTarPWM(-(args[0].toInt()));
      Serial.print("moving left Motor with speed: ");
      Serial.println(args[0]);
      return;
    }
    if(command == "motorRight"){
      if(args.size() != 1){
	Serial.print("error motoRight(speed) requires 1 argument, but ");
	Serial.print(args.size());
	Serial.println(" were given");
	return;
      }
      Encoder_1.setTarPWM(args[0].toInt());
      Serial.print("moving right Motor with speed: ");
      Serial.println(args[0]);
      return;
    } 
    if(command == "turn"){
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
      return;
    } 
}
void loop(){
	Encoder_1.loop();
	Encoder_2.loop();
	//Serial.println("loop");
  	
	/*
	if(Serial3.available()>0){
	  Serial.print((char)Serial3.read());
	}*/
	parse_and_execute_action(read_message());

}
