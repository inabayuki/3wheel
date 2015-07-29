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
    int k=0;
    float xPurpose[10]{250,   0, -250, 0, 250,  250,-250,-250, 0};//x
    float yPurpose[10]{250, 500,  250, 0,   0,  500, 500,   0, 0};//y
    float distanceC=0;
    float integralxC=0;
    float integralyC=0;



public:
    float mokux=0;
    float mokuy=0;
    int period=0;
    float time=0;
    int sw=0;

    Connection();
    void xy(float& distanceC,float&integralxC,float&integralyC);
    void switch0();

    Serial0 serial;
    Sw0 sw0;
    Sw1 sw1;
    Sw2 sw2;
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
#endif//CONTROL_HPP
