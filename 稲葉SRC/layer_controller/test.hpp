//libraries

//application

//controller

//base
#include "system.h"
#include "mcutime.h"

//board
#include "pin.hpp"
#ifndef TEST_HPP
#define TEST_HPP
//circuit
#include "circuit/can_encoder.hpp"

class Testmotor{
public:
	void motortest();
	int b=0;

	Serial0 serial;
	Enc0 enc0;
	Enc1 enc1;
	Enc2 enc2;

	CCW0 ccw0;
	CCW1 ccw1;
	CCW2 ccw2;

	CW0 cw0;
	CW1 cw1;
	CW2 cw2;

	Pwm0 pwm0;
	Pwm1 pwm1;
	Pwm2 pwm2;

	Testmotor(){

		enc0.setup();
		enc1.setup();
		enc2.setup();
		ccw0.setupDigitalOut();
		ccw1.setupDigitalOut();
		ccw2.setupDigitalOut();
		cw0.setupDigitalOut();
		cw1.setupDigitalOut();
		cw2.setupDigitalOut();
		pwm0.setupPwmOut(100000,1.0);
		pwm1.setupPwmOut(100000,1.0);
		pwm2.setupPwmOut(100000,1.0);
		serial.setup(115200);
	}


};
#endif//TEST_HPP
