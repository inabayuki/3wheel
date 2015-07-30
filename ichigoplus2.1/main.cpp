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



int main(void)
{
	Position posi;
	Motor mo;
	Connection connect;

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
			}

			if(millis()-connect.time>1000){
				connect.switch0();
			}

		}
	}
	return 0;
}
