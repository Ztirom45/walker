

#include <motors.hpp>

#include <MeMegaPi.h>
//the makeblock library is not desined well
//therefore i need to include MeMegapi.h in the cpp lib
//and just MeEncoderOnBoard.h in the header
//so that there are no redefinations
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

void init_encoder(){
	Encoder_1.setPulse(8);
	Encoder_1.setRatio(46.67);
	Encoder_1.setPosPid(1.8,0,1.2);
	Encoder_1.setSpeedPid(0.18,0,0);
	
	Encoder_2.setPulse(8);
	Encoder_2.setRatio(46.67);
	Encoder_2.setPosPid(1.8,0,1.2);
	Encoder_2.setSpeedPid(0.18,0,0);

}

