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

	CanEncoder canEncoder0(can,0,5);
	CanEncoder canEncoder1(can,1,5);
	CanEncoder canEncoder2(can,2,5);

	canEncoder0.setup();
	canEncoder1.setup();
	canEncoder2.setup();
	//positiontion position;
	Motor motor;
	Connection connect;
	Testmotor t;

	Position position(canEncoder0,canEncoder1,canEncoder2);

	while(1){
		if(millis()-connect.period>=cycle){
			connect.period=millis();

			if(connect.sw==0){
				connect.switch0();
			}

			if(connect.sw==1){
				position.radian();
				position.selfPosition();
				connect.xy(motor.distance,position.integralx,position.integraly);
				connect.arm();
				if(connect.stopNumber[connect.point]==1){
					motor.armMotor(connect.armpwmC,connect.armcwC,connect.armccwC);
					motor.motorControl(connect.devietionX,connect.devietionY);
					motor.degreeLock(position.degree);
					motor.last();
				}
				else if(connect.stopNumber[connect.point]==0){
					connect.stopMotor();
				}
				motor.dutyCleanUp();
				connect.indication(position.encf[0],position.encf[1],position.encf[2],position.degree,position.integralx,position.integraly);
			}
			if(millis()-connect.time>1000){
				connect.switch0();
			}
		}
	}
	return 0;
}
