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

int main(void)
{
	Can0 can;
	can.setup();
	Buzzer buzzer;

	A1 limBack;
	A3 limFlont;

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

	Position position(canEncoder0,canEncoder1,canEncoder2);
	buzzer.digitalHigh();
	while(1){
		if(millis()-control.period>=cycle){
			control.period=millis();
			if(control.sw==0){
				control.switch0();
			}
			if(control.sw==1){
				position.radian();
				position.selfPosition();

				if(control.spinNumber[control.point]==1){
					motor.motorControl(control.devietionX,control.devietionY);
					motor.degreeLock(position.degree);
					motor.last();
					motor.dutyCleanUp();
					motor.degSw=0;
				}
				else if(control.spinNumber[control.point]==0){
					motor.angel(position.degree,position.degree);
					control.spinControl(position.degree);
				}
				if(control.actionNumber[control.point]==1){
					if(control.armpwm[control.point]==1){
						control.armTime();
					}
					control.arm();
					motor.armMotor(control.armpwmC,control.armcwC,control.armccwC);
				}
				control.xy(position.integralx,position.integraly);
				if(control.point<10){
					control.coordinatePoint();
				}
				else if(control.point>=10){
					buzzer.digitalHigh();

				}
				control.indication(motor.pwmp[0],motor.pwmp[1],motor.pwmp[2],position.degree,position.integralx,position.integraly);
			}
			if(control.sw==3){
				control.test();
			}
			if(millis()-control.time>1000){
				control.switch0();
			}
		}
	}
	return 0;
}

