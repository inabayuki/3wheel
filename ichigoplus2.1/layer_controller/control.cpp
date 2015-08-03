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
	if(stopNumber[point]==0){
		pwm0.pwmWrite(1);
		pwm1.pwmWrite(1);
		pwm2.pwmWrite(1);
	}
}
void Connection::arm(){
	if(millis()-timeLim>1000)
		armpwmC=armpwm[point];
		armcwC=armcw[point];
		armccwC=armccw[point];
	if(millis()-timeLim<=1000){

		if(limFlont.digitalRead()==0){
			armpwmC=0;
			timeLim=millis();
			stopNumber[point]=1;
			return;
		}
		else if(limBack.digitalRead()==0){
			armpwmC=0;
			timeLim=millis();
			stopNumber[point]=1;
			return;
		}
	}
}

void Connection::xy(float& distanceC,float&integralxC,float&integralyC){
	if(distanceC<=1.0&&distanceC!=0){
		point++;
	}
	devietionX=targetX[point]-integralxC;
	devietionY=targetY[point]-integralyC;
	return;
}

void Connection::indication(int&enc0,int&enc1,int&enc2,float&degree,float&integralxC,float&integralyC){

	limitC=limBack.digitalRead();
	serial.printf("%d,%d,%d,%.2f,%.2f,%.2f,%.2f\n\r",enc0,enc1,enc2,degree,integralxC,integralyC,limitC);
	return;
}

