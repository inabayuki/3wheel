//libraries

//application

//controller
#include "layer_controller/blink.hpp"
#include "layer_controller/position.hpp"
#include "layer_controller/motor.hpp"
#include "layer_controller/control.hpp"
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
/*	can.setup();
*/
	CanEncoder can0(can,0,5);
	CanEncoder can1(can,1,5);
	CanEncoder can2(can,2,5);

	can0.setup();
	can1.setup();
	can2.setup();
	//Position posi;
	Motor mo;
	Connection connect;

	Position posi(can0,can1,can2);

	while(1){

		if(millis()-connect.period>=cycle){
			connect.period=millis();
			if(connect.sw==0){
				connect.switch0();
			}
			if(connect.sw==1){
				posi.radian();
				posi.selfPosition();
				connect.xy(mo.distance,posi.integralx,posi.integraly);
				mo.motorControl(connect.mokux,connect.mokuy);
				mo.degreeLock(posi.degree);
				mo.last();
				mo.dutyCleanUp();
				connect.indication(posi.encf[0],posi.encf[1],posi.encf[2],posi.degree,posi.integralx,posi.integraly);
			}

			if(millis()-connect.time>1000){
				connect.switch0();
			}

		}
	}
	return 0;
}
