#include "control.hpp"


Connection::Connection(){

    serial.setup(115200);

    sw0.setupDigitalIn();
	sw1.setupDigitalIn();
	sw2.setupDigitalIn();
	sw3.setupDigitalIn();

	ccw0.setupDigitalOut();
	ccw1.setupDigitalOut();
	ccw2.setupDigitalOut();
	ccw3.setupDigitalOut();

	cw0.setupDigitalOut();
	cw1.setupDigitalOut();
	cw2.setupDigitalOut();
	cw3.setupDigitalOut();

	pwm0.setupPwmOut(100000,1.0);
	pwm1.setupPwmOut(100000,1.0);
	pwm2.setupPwmOut(100000,1.0);
	pwm3.setupPwmOut(100000,1.0);

	potentio.setupDigitalIn();
	limFlont.setupDigitalIn();
	limBack.setupDigitalIn();
	buzzer.setupDigitalOut();
	pote.setupAnalogIn();
}

void Connection::test(float&degree,float&integralxC,float&integralyC){
	serial.printf("%.2f,%.2f,%.2f\n\r",degree,integralxC,integralyC);
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
	else if(sw3.digitalRead()==0&&sw!=3){
		sw=3;
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
void Connection::armTime(){
	if(swArm==0){
		timeArm=millis();
		swArm=1;
	}
}

void Connection::arm(){
	if(millis()-timeArm>=1500){
		armpwm[point]=0;
		spinNumber[point]=1;
		swArm=0;
	}
	armpwmC=armpwm[point];
	armcwC=armcw[point];
	armccwC=armccw[point];
}

void Connection::xy(float integralxC,float integralyC){
	devietionX=targetX[point]-integralxC;
	devietionY=targetY[point]-integralyC;
	distance=hypot(devietionX,devietionY);
	return;
}
void Connection::coordinatePoint(){
	if(distance!=0){
		if(distance<=3.0&&millis()-timepoint>=1500){
			point++;
			timepoint=millis();
		}
	}
	return;
}

void Connection::indication(int&enc0,int&enc1,int&enc2,float&degree,float&integralxC,float&integralyC){

	limitC=limFlont.digitalRead();
	serial.printf("%d,%d,%d,%.2f,%.2f,%.2f,point%d,f%d,b%d\n\r",enc0,enc1,enc2,degree,integralxC,integralyC,point,limFlont.digitalRead(),limBack.digitalRead());
}
