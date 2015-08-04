#include "control.hpp"


Connection::Connection(){

    serial.setup(115200);

    sw0.setupDigitalIn();
	sw1.setupDigitalIn();
	sw2.setupDigitalIn();

	ccw0.setupDigitalOut();
	ccw1.setupDigitalOut();
	ccw2.setupDigitalOut();

	cw0.setupDigitalOut();
	cw1.setupDigitalOut();
	cw2.setupDigitalOut();

	pwm0.setupPwmOut(100000,1.0);
	pwm1.setupPwmOut(100000,1.0);
	pwm2.setupPwmOut(100000,1.0);
	pwm3.setupPwmOut(100000,1.0);

	potentio.setupDigitalIn();
	limFlont.setupDigitalIn();
	limBack.setupDigitalIn();
}

void Connection::switch0(){
	if(sw0.digitalRead()==0&&sw!=1){
		sw=1;
		time=millis();
		return;
	}
	else if(sw1.digitalRead()==0&&sw!=2){
		sw=2;
		time=millis();
	}
	else if(sw2.digitalRead()==0&&sw!=0){
		sw=0;
		pwm3.pwmWrite(1);
		pwm0.pwmWrite(1);
		pwm1.pwmWrite(1);
		pwm2.pwmWrite(1);
		time=millis();
		return;
	}
}

void Connection::stopMotor(){
	if(con!=1){
		pwm0.pwmWrite(1);
		pwm1.pwmWrite(1);
		pwm2.pwmWrite(1);
		con=1;
	}
	if(swi==0){
		if(limBack.digitalRead()==1){
			timeStop=millis();
			swi=1;
		}
		if(limFlont.digitalRead()==1){
			timeStop=millis();
			swi=1;
		}
	}
	if(swi==1){
		if(millis()-timeStop>=3000){
			stopNumber[point]=1;
			swi=0;
		}
	}

}
void Connection::arm(){
	armpwmC=armpwm[point];
	armcwC=armcw[point];
	armccwC=armccw[point];

	if(limFlont.digitalRead()==1){
		if(millis()-timeLim>=2000){
			timeLim=millis();
		}
		if(millis()-timeLim<=1000){
			armpwmC=0;
		}
		return;
	}
	else if(limBack.digitalRead()==1){
		if(millis()-timeLim>=2000){
			timeLim=millis();
		}
		if(millis()-timeLim<=1000){
			armpwmC=0;
		}
		return;
	}


}


void Connection::xy(float&integralxC,float&integralyC){
	devietionX=targetX[point]-integralxC;
	devietionY=targetY[point]-integralyC;
	distance=hypot(devietionX,devietionY);
	if(distance!=0){
		if(millis()-timepoint>=1000){
			if(distance<=2.0){
				point++;
				timepoint=millis();
			}
		}
	}

	return;
}

void Connection::indication(int&enc0,int&enc1,int&enc2,float&degree,float&integralxC,float&integralyC){

	limitC=limFlont.digitalRead();
	serial.printf("%d,%d,%d,%.2f,%.2f,%.2f,%d\n\r",enc0,enc1,enc2,degree,integralxC,integralyC,point);
	return;
}

