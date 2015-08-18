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
	buzzer.setupDigitalOut();
}

void Connection::switch0(){
	if(sw0.digitalRead()==0&&sw!=1){
		sw=1;
		time=millis();
		buzzer.digitalHigh();
	}
	else if(sw1.digitalRead()==0&&sw!=2){
		sw=2;
		time=millis();
		buzzer.digitalHigh();
	}
	else if(sw2.digitalRead()==0&&sw!=0){
		sw=0;
		pwm3.pwmWrite(1);
		pwm0.pwmWrite(1);
		pwm1.pwmWrite(1);
		pwm2.pwmWrite(1);
		time=millis();
		buzzer.digitalHigh();
	}
	if(millis()-time>=500){
		buzzer.digitalLow();
	}
}

void Connection::stopMotor(){
		pwm0.pwmWrite(1);
		pwm1.pwmWrite(1);
		pwm2.pwmWrite(1);
}

void Connection::spinControl(float degreeC){
	if(fabsf(90-degreeC)<=1.0){
		//spinNumber[point]=1;
		actionNumber[point]=1;
	}
}

void Connection::arm(){
	limF=0;
	limB=0;
	if(limFlont.digitalRead()==1){
		limF=1;
	}

	if(limBack.digitalRead()==1){
		limB=1;
	}

	if(oldLimF!=limF){
		if(oldLimB!=limB){
			oldLimB=limB;
			oldLimF=limF;
			timeLim=millis();
			limSw=0;
		}
	}

	if(millis()-timeLim>=1000&&limSw==0){
		//stopNumber[point]=1;
		armpwm[point]=0;
		spinNumber[point]=1;
		limSw=1;
	}
	armpwmC=armpwm[point];
	armcwC=armcw[point];
	armccwC=armccw[point];
}

void Connection::xy(float integralxC,float integralyC){
	devietionX=targetX[point]-integralxC;
	devietionY=targetY[point]-integralyC;
	distance=hypot(devietionX,devietionY);
	if(distance!=0){
		if(distance<=10.0&&millis()-timepoint>=200){
			point++;
			timepoint=millis();
		}
	}
	return;
}

void Connection::indication(float&enc0,float&enc1,float&enc2,float&degree,float&integralxC,float&integralyC){

	limitC=limFlont.digitalRead();
	serial.printf("%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%d\n\r",enc0,enc1,enc2,degree,integralxC,integralyC,point);
	return;
}
