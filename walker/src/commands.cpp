#include "sensors.hpp"
#include <commands.hpp>

Command::Command(String command,
		void (*setup)(Vector<String>,Command*),
		void (*loop)(Command*)
):command(command),setup(setup),loop(loop),speed(0){

}




void forward_setup(Vector<String> args,Command *command){
      if(args.size() != 1){
	mylog("forward(speed) expected 1 argument, but ");
	mylog(args.size());
	mylog(" were given");
	return;
      }
      int16_t speed = args[0].toInt();
      Encoder_1.setTarPWM(speed);
      Encoder_2.setTarPWM(-(speed));
      //Encoder_2.setTarPWM(50.0);
      //Encoder_1.setTarPWM(-55.0);
      mylog("driving forward with speed: ");
      mylog(speed);
}
void forward_loop(Command *command){}

void stop_setup(Vector<String> args,Command *command){
      if(args.size() != 0){
	mylog("stop() expected 0 argument, but ");
	mylog(args.size());
	mylog(" were given");
	return;
      }
      Encoder_1.setTarPWM(0);
      Encoder_2.setTarPWM(0);
      mylog("stopped");
}
void stop_loop(Command *command){
}

void motor_right_setup(Vector<String> args,Command *command){
      if(args.size() != 1){
	mylog("error motorRight(speed) expected 1 argument, but ");
	mylog(args.size());
	mylog(" were given");
	return;
      }
      Encoder_1.setTarPWM(args[0].toInt());
      mylog("driving forward with speed: ");
      mylog(args[0]);
}
void motor_right_loop(Command *command){}

void motor_left_setup(Vector<String> args,Command *command){
      if(args.size() != 1){
	mylog("error motorLeft(speed) expected 1 argument, but ");
	mylog(args.size());
	mylog(" were given");
	return;
      }
      Encoder_2.setTarPWM(-args[0].toInt());
      mylog("driving forward with speed: ");
      mylog(args[0]);
}

void motor_left_loop(Command *command){}

void turn_setup(Vector<String> args,Command *command){
      if(args.size() != 1){
	mylog("error turn(speed) requires 1 argument, but ");
	mylog(args.size());
	mylog(" were given");
	return;
      }
      Encoder_1.setTarPWM(args[0].toInt());
      Encoder_2.setTarPWM(args[0].toInt());
      mylog("turning right Motor with speed: ");
      mylog(args[0]);
}
void turn_loop(Command *command){}

void follow_wall_setup(Vector<String> args,Command *command){
      if(args.size() != 0){
	mylog("error: follow_wall() requires 0 argument, but ");
	mylog(args.size());
	mylog(" were given");
	return;
      } 
}

void follow_wall_loop(Command *command){
	float u1 = read_ultrasonic1();
	float u2 = read_ultrasonic2();
	float us_div = u1-u2;
	mylog(" 1:");
	mylog(u1);
	mylog(" 2:");
	mylog(u2);
	mylog(" div:");
	mylog(us_div*STEARING_FAKTOR);
	Encoder_1.setTarPWM(-100-us_div*STEARING_FAKTOR);
	Encoder_2.setTarPWM(100+us_div*STEARING_FAKTOR);
	Encoder_1.loop();
	Encoder_2.loop();
	
}

#ifdef LEG_TRACKING_ENABLET
void leg1_move(int speed,int direction){	
	sensors_event_t event;
	
	Encoder_1.setTarPWM(speed);
	while(direction*event.gyro.y>0||event.gyro.y==0){	
	  acc2.getEvent(&event);
	  mylog("A_x: "); mylog(event.gyro.x); mylog(", ");
	  mylog("A_y: "); mylog(event.gyro.y); mylog(", ");
	  mylog("A_z: "); mylog(event.gyro.z); mylog(" ");
	  
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
	  mylog("B_x: "); mylog(event.gyro.x); mylog(", ");
	  mylog("B_y: "); mylog(event.gyro.y); mylog(", ");
	  mylog("B_z: "); mylog(event.gyro.z); mylog(" ");
	  
	  Encoder_1.loop();
	  Encoder_2.loop();
	}
	Encoder_2.setTarPWM(0);

}
void forward_legwise_setup(Vector<String> args,Command *command){
      if(args.size() != 1){
	mylog("error: forward_legwise(speed) requires 1 argument, but ");
	mylog(args.size());
	mylog(" were given");
	return;
      } 
      command->speed = args[0].toInt();
      mylog("walking legwise with speed: ");
      mylog(command->speed);

}
void forward_legwise_loop(Command *command){
      mylog("hi");
      leg1_move(-command->speed,1);
      leg1_move(-command->speed,-1);
      leg2_move(command->speed, 1);
      leg2_move(command->speed, -1);

}
#endif 
void forward_gyro_setup(Vector<String> args,Command *command){
    //reset gyro
    gyro.gyro_x = 0;
    gyro.gyro_y = 0;
    gyro.gyro_z = 0;

    if(args.size() != 1){
	mylog("error: forward_gyro(speed) requires 1 argument, but ");
	mylog(args.size());
	mylog(" were given");
	return;
      } 
      command->speed = args[0].toInt();
      mylog("walking legwise with speed: ");
      mylog(command->speed);

}
void forward_gyro_loop(Command *command){//TODO: debug gyro does not work output: 0.0
      const float stiring = gyro.gyro_x*STEARING_FAKTOR; 
      Encoder_1.setTarPWM(command->speed-stiring);
      Encoder_2.setTarPWM(-command->speed-stiring);
      mylog(gyro.gyro_x);
      mylog(", ");
      mylog(stiring);
      mylog(", ");
      mylog(-command->speed+stiring); 
      mylog(", ");
      mylog(command->speed+stiring);
}

Command commands[COMMAND_COUNT] ={
	Command("stop",&stop_setup,&stop_loop),
	Command("forward",&forward_setup,&forward_loop),    
	Command("motor_right",&motor_right_setup,&motor_right_loop),
	Command("motor_left",&motor_left_setup,&motor_left_loop),
	Command("turn",&turn_setup,&turn_loop),
	Command("follow_wall",&follow_wall_setup,&follow_wall_loop),
	#ifdef LEG_TRACKING_ENABLET
	Command("forward_legwise",&forward_legwise_setup,&forward_legwise_loop),
	#endif
	Command("forward_gyro",&forward_gyro_setup,&forward_gyro_loop)
};

size_t current_command = 0;
String storage_array[MAX_COMMAND_LEN];
Vector<String> args(storage_array);

void parse_and_execute_action(String action){
  if(action==""){//string is empty
      commands[current_command].loop(&commands[current_command]);
      return;
    }
    mylog(action);
    
    args.clear();
    int pos = action.lastIndexOf(" ");
    while (pos != -1) {//separates string in reverse order and pushes to args
	String token = action.substring(pos, action.length());
	
	args.push_back(token);

	action.remove(pos, pos + token.length());
	pos = action.lastIndexOf(" ");

    }
    for(int i=0;i<COMMAND_COUNT;i++){
      if(commands[i].command == action){
	commands[i].setup(args,&commands[i]);
	current_command = i;
	return;
      }

    }

}
