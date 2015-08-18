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
#define pGaina 1.0/M_PI
#define dGaina 0.4
#define pGain 1.0/180.0	//p gain
#define dGain 0.4		//d gain

class Motor{
private:
    float deg=0;
    float pwmLock[3]={0,0,0};
    float pwmCood[3]{0,0,0};
    float degreeOld=0;
    float *devietionXc=0;
    float *devietionYc=0;
    float tmp=0;
    float tmp1=0;
    float *degree1=0;
    float dControl=0;
    float dControlA=0;
    float radOld=0;
    float *rad=0;
    float *xC;
    float rightAngel=M_PI;
    float degreeDivietion=0;
    float *degree2;


    int *armpwm=0;
    int *armcw=0;
    int *armccw=0;
    int timedegree=0;

public:
    float distance=0;
    int degSw=0;
    float pwmp[4]={1,1,1,0};
    float radAppoint=90;
    float degreeAppoint=0;
    Motor();
    void armMotor(int armpwm,int armcw,int armccw);
    void motorControl(float devietionXc,float devietionYc);
    void xCoordinateMotor(float xC);
    void degreeLock(float degree1);
    void dutyCleanUp();
    void last();
    void angel(float degree1,float degree2);
    void xCoordinateClear();

    CCW0 ccw0;
	CCW1 ccw1;
	CCW2 ccw2;
	CCW3 ccw3;

	CW0 cw0;
	CW1 cw1;
	CW2 cw2;
	CW3 cw3;

	Pwm0 pwm0;
	Pwm1 pwm1;
	Pwm2 pwm2;
	Pwm3 pwm3;

	A3 limFlont;
	A1 limBack;

};
#endif//MOTOR_HPP
