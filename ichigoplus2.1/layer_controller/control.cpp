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
	limFlont.setupAnalogIn();
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
	if(limFlont.analogRead()==0){
		pwm3.pwmWrite(1);
		time=millis();
		return;
	}
}

void Connection::xy(float& distanceC,float&integralxC,float&integralyC){
	if(distanceC<=1.0&&k!=9){
		k++;
	}
	devietionX=targetX[k]-integralxC;
	devietionY=targetY[k]-integralyC;
	return;
}

void Connection::indication(int&enc0,int&enc1,int&enc2,float&degree,float&integralxC,float&integralyC){

	limitC=limFlont.analogRead();
	serial.printf("%d,%d,%d,%.2f,%.2f,%.2f,%.2f\n\r",enc0,enc1,enc2,degree,integralxC,integralyC,limitC);
	return;
}

