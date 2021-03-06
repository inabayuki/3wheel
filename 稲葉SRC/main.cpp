//libraries

//application

//controller
#include "layer_controller/blink.hpp"
#include "layer_controller/position.hpp"
#include "layer_controller/motor.hpp"
#include "layer_controller/control.hpp"
#include "layer_controller/test.hpp"

//base
#include "system.h"
#include "mcutime.h"

//board
#include "pin.hpp"

//circuit
#include "circuit/can_encoder.hpp"
#include "circuit/r1350n.hpp"

int main(void)
{
	Can0 can;
	can.setup();
	Buzzer buzzer;
	Led0 led0;
	Led1 led1;
	Led2 led2;
	Led3 led3;

	A1 limBack;
	A3 limFlont;
	Serial1 serial1;
	led0.setupDigitalOut();
	led1.setupDigitalOut();
	led2.setupDigitalOut();
	led3.setupDigitalOut();
	buzzer.setupDigitalOut();
	CanEncoder canEncoder0(can,0,5);
	CanEncoder canEncoder1(can,1,5);
	CanEncoder canEncoder2(can,2,5);

	canEncoder0.setup();
	canEncoder1.setup();
	canEncoder2.setup();

	Motor motor;
	Connection control;
	Testmotor t;
	R1350n r1350n(serial1);
	r1350n.setup();
	int timeLed=0;

	Position position(canEncoder0,canEncoder1,canEncoder2);
	buzzer.digitalHigh();
	while(1){

		if(control.dispose==0){
			led0.digitalWrite(1);
		}
		else if(control.dispose==1){
			led1.digitalWrite(1);
		}
		else if(control.dispose==2){
			led2.digitalWrite(1);
		}
		if(control.member==1){
			led3.digitalWrite(1);
		}
		else if(control.member==2){
			if(millis()-timeLed>=500){
				led3.digitalToggle();
				timeLed=millis();
			}
		}
		if(millis()-control.period>=cycle){
			control.period=millis();
			if(control.sw==0&&millis()-control.time>1000){
				control.switch0();
			}
			if(control.sw==1){
				position.radian(r1350n.angle());
				position.selfPosition();
				control.xy(position.integralx,position.integraly);
				if(control.spinNumber[control.member][control.dispose][control.point]==1){
					motor.motorControl(control.devietionX,control.devietionY);
					motor.degreeLock(position.rad);
				//	motor.testmotor();
					motor.last();
					motor.dutyCleanUp();
					if(control.point<5){
						control.coordinatePoint(motor.distance);
					}
				}
				else if(control.spinNumber[control.member][control.dispose][control.point]==0){
					motor.angle(position.degree,position.degree);
					control.spinControl(position.degree);
				}
				if(control.actionNumber[control.member][control.dispose][control.point]==1){
					if(control.armpwm[control.member][control.dispose][control.point]!=0){
						control.armTime();
					}
					control.arm();
					motor.armMotor(control.armpwmC,control.armcwC,control.armccwC);

				}




				control.indication(position.encf[0],position.encf[1],position.encf[2],position.degree,position.integralx,position.integraly,r1350n.angle());
			}

			if(millis()-control.time>1000){
				control.switch0();
			}
		}
	}
	return 0;
}

