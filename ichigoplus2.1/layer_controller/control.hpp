//libraries
#include <math.h>

//application

//controller

//base
#include "system.h"
#include "mcutime.h"

//board
#include "pin.hpp"
#ifndef CONTROL_HPP
#define CONTROL_HPP
//circuit
#define cycle 5

class Connection{
private:
	int timepoint=0;
	int timeStop=5000000000;
    int timeSpin=0;
    int timeMotor=0;
    int con1=0;
    int swi=0;
    int oldLimF=1;
    int oldLimB=0;
    int limB=0;
    int limF=0;
	float *rad;
    float distance=0;
    float *integralxC;
    float *integralyC;
    float *enc0,*enc1,*enc2;
    float *degreeC;
    float timeArm=0;
    int limSw=1;


public:
    int swArm=0;
    float targetX[10]{   0,   0,-750,-750,-750,   0,   0,-1750,-1750};//x
    float targetY[10]{1930,1250,1250,   0, 850,1930,1800,  400,    0};//y
    int   stopNumber[10]{1,0,1,0,1,1,0,0,1,1};
    int   spinNumber[10]{1,0,1,1,1,1,0,1,1,1};
    int actionNumber[10]{1,0,1,1,1,1,0,1,1,1};
    int       armpwm[10]{0,1,1,0,0,0,1,1,0,0};
   	int        armcw[10]{1,1,0,1,1,1,1,0,1,1};
   	int       armccw[10]{1,0,1,1,1,1,0,1,1,1};
    int point=0;
    int con=1;
    int number=0;
    float *radAppoint=0;
    float limit1=0;
    float devietionX=0;
    float devietionY=0;
    float time=0;
    float limitC=0;
    int sw=0;
    int period=0;
    int armpwmC=0;
    int armcwC=0;
    int armccwC=0;
    Connection();
    void xy(float integralxC,float integralyC);
    void coordinatePoint();
    void switch0();
    void indication(float&enc0,float&enc1,float&enc2,float&degree,float&integralxC,float&integralyC);
    void arm();
    void spinControl(float degreeC);
    void stopMotor();
    void armTime();
    void test();

    Serial0 serial;

    Sw0 sw0;
    Sw1 sw1;
    Sw2 sw2;
    Sw3 sw3;
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
	A1 limBack;
	A2 potentio;
	A3 limFlont;
	A4 pote;
	Buzzer buzzer;
};
#endif//CONTROL_HPP
