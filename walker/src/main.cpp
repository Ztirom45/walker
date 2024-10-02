/*
a siple test program for my robot Setup written with c++ and PlatformIo
there are No Competible Motor Driver Pins or general PWM pins to power the Motors of my Robot
=> The RObot Setup Doesn't Work

LICENCE: GPL4
written by Ztirom45
*/


#include <motors.hpp>



#include <HardwareSerial.h>
#include <Arduino.h>
#include <Adafruit_ADXL345_U.h>
#include <Vector.h>


//sensors
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

#define read_ultrasonic1() ultrasonic_cm(28,30,0.034 / 2.0)
#define read_ultrasonic2() ultrasonic_cm(29,39,0.034 / 2.0)
/* Assign a unique ID to this sensor at the same time */
Adafruit_ADXL345_Unified acc = Adafruit_ADXL345_Unified(12345);
Adafruit_ADXL345_Unified acc2 = Adafruit_ADXL345_Unified(12344);

#include <commands.hpp>

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
	
	//setup motors
	attachInterrupt(Encoder_1.getIntNum(), isr_process_encoder1, RISING);
	attachInterrupt(Encoder_1.getIntNum(), isr_process_encoder1, RISING);
	//setup for encoder, wich wont work anyways
	//use with: runSpeed
	//setup wifimod
	//Serial3.begin(115200);
	//wait_for_wifi_connection();
	
	//setup command engine
	init_encoder();
	//init_commands(&Encoder_1,&Encoder_2);
}

//wall follower
void follow_wall(){
	float u1 = read_ultrasonic1();
	float u2 = read_ultrasonic2();
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
	Serial.print("error stop() requires 0 argument, but ");
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
    if(command == "follow_wall"){
      if(args.size() != 0){
	Serial.print("error follow_wall() requires 0 argument, but ");
	Serial.print(args.size());
	Serial.println(" were given");
	return;
      } 
      Serial.println("following wall");
      while(true){
	follow_wall();
      }
      return;
    }   

}

void leg1_move(int speed,int direction){	
	sensors_event_t event;
	
	Encoder_1.setTarPWM(speed);
	while(direction*event.gyro.y>0||event.gyro.y==0){	
	  acc2.getEvent(&event);
	  Serial.print("A_x: "); Serial.print(event.gyro.x); Serial.print(", ");
	  Serial.print("B_y: "); Serial.print(event.gyro.y); Serial.print(", ");
	  Serial.print("C_z: "); Serial.print(event.gyro.z); Serial.println(" ");
	  
	  Encoder_2.loop();
	  Encoder_1.loop();
	}
	Encoder_1.setTarPWM(0);


}
void leg2_move(int speed,int direction){	
	sensors_event_t event;
	
	Encoder_2.setTarPWM(speed);
	while(direction*event.gyro.y>0||event.gyro.y==0){	
	  acc.getEvent(&event);
	  Serial.print("A_x: "); Serial.print(event.gyro.x); Serial.print(", ");
	  Serial.print("B_y: "); Serial.print(event.gyro.y); Serial.print(", ");
	  Serial.print("C_z: "); Serial.print(event.gyro.z); Serial.println(" ");
	  
	  Encoder_1.loop();
	  Encoder_2.loop();
	}
	Encoder_2.setTarPWM(0);

}

void walk(){//the motors spin in diffrent speeds, so the program needs to compansate this
	leg1_move(-80,1);
	leg1_move(-80,-1);
	leg2_move(75, 1);
	leg2_move(75, -1);

}

void loop(){
	Encoder_1.loop();
	Encoder_2.loop();

	/*//debuging stuff
	if(Serial3.available()>0){
	  Serial.print((char)Serial3.read());
	}*/
	//Encoder_2.setTarPWM(50.0);
	//Encoder_1.setTarPWM(-55.0);
	
	walk();
}
