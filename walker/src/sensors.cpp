
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

Gyro::Gyro() : gyro_x(0),gyro_y(0),gyro_z(0){};
void Gyro::init(){

      if (!mpu.begin()) {
	Serial.println("Failed to find MPU6050 chip");
      }
      mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
      mpu.setGyroRange(MPU6050_RANGE_500_DEG);
      mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
      //disable unnnesery features of sensor, beacuse of performance
      mpu.setTemperatureStandby(true);
      mpu.setAccelerometerStandby(true, true, true);

}

void Gyro::update(){
  //try None
  this->mpu.getEvent(&this->a, &this->g, &this->temp);
  
  this->gyro_x += this->g.gyro.x+0.205;
  Serial.println(this->gyro_x);
  if(this->gyro_x>6.28){this->gyro_x-=12.56;}
  if(this->gyro_x<-6.28){this->gyro_x+=12.56;}
  
  this->gyro_y += this->g.gyro.y-0.02;
  if(this->gyro_y>6.28){this->gyro_y-=12.56;}
  if(this->gyro_y<-6.28){this->gyro_y+=12.56;} 
  
  this->gyro_z += this->g.gyro.z+0.05;
  if(this->gyro_z>6.28){this->gyro_z-=12.56;}
  if(this->gyro_z<-6.28){this->gyro_z+=12.56;}
}

void init_sensors(){
	//setup sensors
	#ifdef LEG_TRACKING_ENABLET
	if(!acc.begin(0x53))
	{
	  Serial.println("no ADXL345 on 53d detected ... Check your wiring!");
	}
	if(!acc2.begin(0x1d))
	{
	  Serial.println("no ADXL345 on 0x1d detected ... Check your wiring!");
	}
	acc.setRange(ADXL345_RANGE_16_G);
	acc2.setRange(ADXL345_RANGE_16_G);
	#endif
	gyro.init();
}
