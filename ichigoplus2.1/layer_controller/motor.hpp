//libraries
#include <math.h>

//application

//controller

//base
#include "system.h"
#include "mcutime.h"

//board
#include "pin.hpp"
#ifndef MOTOR_HPP
#define MOTOR_HPP

//circuit
#define pGain 1.0/180.0	//p gain
#define dGain 0.6		//d gain

class Motor{
private:
    float deg=0;

    float pwmLock[3]={0,0,0};
    float degreeOld=0;
    float mokuxC=0;
    float mokuyC=0;
    float tmp=0;
    float tmp1=0;
    float degree1=0;
    float dControl=0;
public:
    float distance=0;
    float pwmp[3]={1,1,1};
    Motor();
    void motorControl(float& mokuxC,float& mokuyC);
    void degreeLock(float& degree1);
    void dutyCleanUp();
    void last();

    CCW0 ccw0;
	CCW1 ccw1;
	CCW2 ccw2;
	CW0 cw0;
	CW1 cw1;
	CW2 cw2;
	Pwm0 pwm0;
	Pwm1 pwm1;
	Pwm2 pwm2;
};
#endif//MOTOR_HPP
