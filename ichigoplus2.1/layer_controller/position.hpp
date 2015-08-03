//libraries
#include <math.h>

//application

//controller

//base
#include "system.h"
#include "mcutime.h"

//board
#include "pin.hpp"
#ifndef POSITION_HPP
#define POSITION_HPP
//circuit
#include "circuit/can_encoder.hpp"
#include "can.hpp"
#define l 115//enc distance from the center
#define pGain 1.0/180.0	//p gain
#define dGain 0.6		//d gain
#define	diameter 30
#define cycle 5

class Position{
private:
	float encDistance[3]={0,0,0};
    float oldEncDistance[3]={0,0,0};
    float newEncDistance[3]={0,0,0};

    float x=0;
	float y=0;
	float firstX=0;
	float secondX=0;
	float thirdX=0;
	float firstY=0;
	float secondY=0;
	float thirdY=0;
	int divide=0;

public:
	Serial0 serial;
	Enc0 enc0;
	Enc1 enc1;
	Enc2 enc2;
	Can0 can;
	Encoder *canEncC0;
	Encoder *canEncC1;
	Encoder *canEncC2;
    float rad=0;
    float degree=0;
    float integralx=0;
    float integraly=0;
    int encf[3]{0,0,0};

    Position(Encoder &canEncC0,Encoder &canEncC1,Encoder &canEncC2){

    	this->canEncC0 = &canEncC0;
		this->canEncC1 = &canEncC1;
		this->canEncC2 = &canEncC2;

		serial.setup(115200);
		enc0.setup();
		enc1.setup();
		enc2.setup();

    }
    void radian();
    void selfPosition();
};
#endif//POSITION_HPP
