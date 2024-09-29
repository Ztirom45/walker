/*
motor lib
*/
#pragma once

#include <MeEncoderOnBoard.h>
//#include <MeMegaPi.h>
//motors


extern MeEncoderOnBoard Encoder_1;
extern MeEncoderOnBoard Encoder_2;
extern MeEncoderOnBoard Encoder_3;
extern MeEncoderOnBoard Encoder_4;

void isr_process_encoder1(void);
void isr_process_encoder2(void);

void init_encoder();

