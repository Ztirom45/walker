#include "HardwareSerial.h"
#include <commands.hpp>

Command::Command(String command,
		void (*setup)(Vector<String>,Command*),
		void (*loop)(Command*)
):command(command),setup(setup),loop(loop),speed(0){

}




void forward_setup(Vector<String> args,Command *command){
      if(args.size() != 1){
	Serial.print("forward(speed) expected 1 argument, but ");
	Serial.print(args.size());
	Serial.println(" were given");
	return;
      }
      int16_t speed = args[0].toInt();
      Encoder_1.setTarPWM(speed);
      Encoder_2.setTarPWM(-(speed));
      //Encoder_2.setTarPWM(50.0);
      //Encoder_1.setTarPWM(-55.0);
      Serial.print("driving forward with speed: ");
      Serial.println(speed);
}
void forward_loop(Command *command){}

void stop_setup(Vector<String> args,Command *command){
      if(args.size() != 0){
	Serial.print("stop() expected 0 argument, but ");
	Serial.print(args.size());
	Serial.println(" were given");
	return;
      }
      Encoder_1.setTarPWM(0);
      Encoder_2.setTarPWM(0);
      Serial.print("stopped");
}
void stop_loop(Command *command){
}

void motor_right_setup(Vector<String> args,Command *command){
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
void motor_right_loop(Command *command){}

void motor_left_setup(Vector<String> args,Command *command){
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

void motor_left_loop(Command *command){}

void turn_setup(Vector<String> args,Command *command){
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
void turn_loop(Command *command){}

void follow_wall_setup(Vector<String> args,Command *command){
      if(args.size() != 0){
	Serial.print("error: follow_wall() requires 0 argument, but ");
	Serial.print(args.size());
	Serial.println(" were given");
	return;
      } 
}

void follow_wall_loop(Command *command){
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

void forward_legwise_setup(Vector<String> args,Command *command){
      if(args.size() != 1){
	Serial.print("error: forward_legwise(speed) requires 1 argument, but ");
	Serial.print(args.size());
	Serial.println(" were given");
	return;
      } 
      command->speed = args[0].toInt();
      Serial.print("walking legwise with speed: ");
      Serial.println(command->speed);

}
void forward_legwise_loop(Command *command){
      Serial.println("hi");
      leg1_move(-command->speed,1);
      leg1_move(-command->speed,-1);
      leg2_move(command->speed, 1);
      leg2_move(command->speed, -1);

}
void forward_gyro_setup(Vector<String> args,Command *command){
      if(args.size() != 1){
	Serial.print("error: forward_legwise(speed) requires 1 argument, but ");
	Serial.print(args.size());
	Serial.println(" were given");
	return;
      } 
      command->speed = args[0].toInt();
      Serial.print("walking legwise with speed: ");
      Serial.println(command->speed);

}
void forward_gyro_loop(Command *command){
      Serial.println("hi");
      leg1_move(-command->speed,1);
      leg1_move(-command->speed,-1);
      leg2_move(command->speed, 1);
      leg2_move(command->speed, -1);

}

Command commands[COMMAND_COUNT] ={
	Command("stop",&stop_setup,&stop_loop),
	Command("forward",&forward_setup,&forward_loop),    
	Command("motor_right",&motor_right_setup,&motor_right_loop),
	Command("motor_left",&motor_left_setup,&motor_left_loop),
	Command("turn",&turn_setup,&turn_loop),
	Command("follow_wall",&follow_wall_setup,&follow_wall_loop),
	Command("forward_gyro",&forward_gyro_setup,&forward_gyro_loop)
};

size_t current_command = 0;

void parse_and_execute_action(String action){
    if(action == ""){
      commands[current_command].loop(&commands[current_command]);
      return;
    }
    Serial.println(action);
    String storage_array[MAX_COMMAND_LEN];
    Vector<String> args(storage_array);
     
    action.remove(action.length()-2, action.length());//remove \n 
    int pos = action.lastIndexOf(" ");
    while (pos != -1) {//separates string in reverse order and pushes to args
        String token = action.substring(pos, action.length());
	
	args.push_back(token);
        action.remove(pos, pos + token.length());
	pos = action.lastIndexOf(" ");
    }
    for(int i=0;i<COMMAND_COUNT;i++){
      Serial.println(i);
      if(commands[i].command == action){
	commands[i].setup(args,&commands[i]);
	current_command = i;
	return;
      }

    }

}
