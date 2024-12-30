#include <sensors.hpp>


Adafruit_ADXL345_Unified acc = Adafruit_ADXL345_Unified(12345);
Adafruit_ADXL345_Unified acc2 = Adafruit_ADXL345_Unified(12344);
Gyro gyro;

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

Gyro::Gyro() : gyro_x(0),gyro_y(0),gyro_z(0),delta_gyro_x(0),delta_gyro_y(0),delta_gyro_z(0){};

void Gyro::init(){

      if (!mpu.begin()) {
	mylog("Failed to find MPU6050 chip");
      }
      mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
      mpu.setGyroRange(MPU6050_RANGE_500_DEG);
      mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
      //disable unnnesery features of sensor, beacuse of performance
      mpu.setTemperatureStandby(true);
      mpu.setAccelerometerStandby(true, true, true);
      
      this->calibrate();
}

void Gyro::calibrate(){
  for(int i=0;i<100;i++){
    this->mpu.getEvent(&this->a, &this->g, &this->temp);
    this->delta_gyro_x += g.gyro.x;
    this->delta_gyro_y += g.gyro.y;
    this->delta_gyro_z += g.gyro.z;
  }
  this->delta_gyro_x /= 100;
  this->delta_gyro_y /= 100;
  this->delta_gyro_z /= 100;
  mylog("gyro calibration: gxa=");
  mylog(this->delta_gyro_z);
  mylog(", gya=");
  mylog(this->delta_gyro_y);
  mylog(", gza=");
  mylog(this->delta_gyro_z);
}
void Gyro::update(){
  this->mpu.getEvent(&this->a, &this->g, &this->temp);
  
  this->gyro_x += n_decimals(this->g.gyro.x-this->delta_gyro_x,10);
  //if(this->gyro_x>6.28){this->gyro_x-=12.56;}
  //if(this->gyro_x<-6.28){this->gyro_x+=12.56;}
  
  this->gyro_y += n_decimals(this->g.gyro.y-this->delta_gyro_y,10);
  //if(this->gyro_y>6.28){this->gyro_y-=12.56;}
//if(this->gyro_y<-6.28){this->gyro_y+=12.56;} 
  
  this->gyro_z += n_decimals(this->g.gyro.z-this->delta_gyro_z,10);
  //if(this->gyro_z>6.28){this->gyro_z-=12.56;}
  //if(this->gyro_z<-6.28){this->gyro_z+=12.56;}
}

void init_sensors(){
	//setup sensors
	#ifdef LEG_TRACKING_ENABLET
	if(!acc.begin(0x53))
	{
	  mylog("no ADXL345 on 53d detected ... Check your wiring!");
	}
	if(!acc2.begin(0x1d))
	{
	  mylog("no ADXL345 on 0x1d detected ... Check your wiring!");
	}
	acc.setRange(ADXL345_RANGE_16_G);
	acc2.setRange(ADXL345_RANGE_16_G);
	#endif
	gyro.init();
}
