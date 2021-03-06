#include "motor.hpp"

Motor::Motor(){
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
	limFlont.setupDigitalIn();
	limBack.setupDigitalIn();

}
void Motor::armMotor(int armpwm,int armcw,int armccw){
	pwm3.pwmWrite(1.0-armpwm);
	cw3.digitalWrite(armcw);
	ccw3.digitalWrite(armccw);
	return;
}

void Motor::motorControl(float devietionXc,float devietionYc){
	deg=atan2f(devietionYc,devietionXc);
	distance=hypot(devietionXc,devietionYc);
	pwmp[0]=sinf(deg-M_PI/6.0);
	pwmp[2]=cosf(deg);
	pwmp[1]=-1*sinf(M_PI/6.0+deg);

	tmp=fabsf(pwmp[0]);

	for(int i=1;i<=2;i++){
		if(tmp<fabsf(pwmp[i])){
			tmp=fabsf(pwmp[i]);
		}
	}
	for(int i=0;i<=2;i++){
		pwmp[i]=pwmp[i]/fabsf(tmp);
	}
	for(int i=0;i<=2;i++){
		pwmp[i]=pwmp[i]*0.9;
	}
	return;
}

void Motor::degreeLock(float rad){
	dControl+=(rad-radOld)*dGaina;
	radOld=rad;
	for(int i=0;i<=2;i++){
		pwmLock[i]=rad*pGaina+dControl;
	}
	return;
}
/*
void Motor::degreeLock(float degree1){
	dControl+=(degree1-degreeOld)*dGain;
	degreeOld=degree1;
	for(int i=0;i<=2;i++){
		pwmLock[i]=degree1*pGain+dControl;
	}
	for(int i=0;i<=2;i++){
		pwmLock[i]=pwmLock[i];
	}
	return;
}
*/
void Motor::xCoordinateClear(){
	for(int i=0;i<=2;i++){
		pwmCood[i]=0;
	}
}
void Motor::testmotor(){
	cw0.digitalWrite(1);
	ccw0.digitalWrite(0);
	cw1.digitalWrite(1);
	ccw1.digitalWrite(0);
	cw2.digitalWrite(1);
	ccw2.digitalWrite(0);
	for(int i=0;i<=2;i++){
		if(pwmLock[i]<0){
			if(i==0){
				cw0.digitalWrite(0);
				ccw0.digitalWrite(1);
				pwmLock[i]=pwmLock[i]*-1;
			}
			if(i==1){
				cw1.digitalWrite(0);
				ccw1.digitalWrite(1);
				pwmLock[i]=pwmLock[i]*-1;
			}
			if(i==2){
				cw2.digitalWrite(0);
				ccw2.digitalWrite(1);
				pwmLock[i]=pwmLock[i]*-1;
			}
		}
	}

	pwm0.pwmWrite(1-pwmLock[0]);
	pwm1.pwmWrite(1-pwmLock[1]);
	pwm2.pwmWrite(1-pwmLock[2]);
}
void Motor::xCoordinateMotor(float xC){
	rightAngle=0;
	if(xC<0){
		rightAngle=M_PI;
	}
	pwmCood[0]=sin(rightAngle-M_PI/6.0);
	pwmCood[2]=cos(rightAngle);
	pwmCood[1]=-1*sin(M_PI/6.0+rightAngle);
	tmp=fabsf(pwmCood[0]);

	for(int i=1;i<=2;i++){
		if(tmp<fabsf(pwmCood[i])){
			tmp=fabsf(pwmCood[i]);
		}
	}
	for(int i=0;i<=2;i++){
		pwmCood[i]=pwmCood[i]/fabsf(tmp);
	}
	for(int i=0;i<=2;i++){
		pwmCood[i]=pwmCood[i]/10.0;
	}
	return;
}

void Motor::angle(float degree1,float degree2){

	degree1=degree1-degreeAppoint;
	dControlA+=(degree1-degreeOld)*dGain;
	for(int i=0;i<=2;i++){
		pwmp[i]=degree1*pGain+dControlA;
	}
	cw0.digitalWrite(1);
	ccw0.digitalWrite(0);
	cw1.digitalWrite(1);
	ccw1.digitalWrite(0);
	cw2.digitalWrite(1);
	ccw2.digitalWrite(0);
	for(int i=0;i<=2;i++){
		if(pwmp[i]<0){
			if(i==0){
				cw0.digitalWrite(0);
				ccw0.digitalWrite(1);
				pwmp[i]=pwmp[i]*-1;
			}
			if(i==1){
				cw1.digitalWrite(0);
				ccw1.digitalWrite(1);
				pwmp[i]=pwmp[i]*-1;
			}
			if(i==2){
				cw2.digitalWrite(0);
				ccw2.digitalWrite(1);
				pwmp[i]=pwmp[i]*-1;
			}
		}
	}
	pwm0.pwmWrite(1.0-pwmp[0]);
	pwm1.pwmWrite(1.0-pwmp[1]);
	pwm2.pwmWrite(1.0-pwmp[2]);
	degreeOld=degree1;
	degreeDivietion=degreeAppoint-degree2;
	if(degreeAppoint!=75&&millis()-timedegree>=100){
		degreeAppoint+=5;
		timedegree=millis();
	}
}
void Motor::dutyCleanUp(){
	pwm0.pwmWrite(1.0-pwmp[0]);
	pwm1.pwmWrite(1.0-pwmp[1]);
	pwm2.pwmWrite(1.0-pwmp[2]);
	return;
}

void  Motor::last(){

	for(int i=0;i<=2;i++){
		pwmp[i]=pwmp[i]-pwmLock[i];
	}
    tmp1=fabsf(pwmp[0]);

	for(int i=1;i<=2;i++){
		if(tmp1<fabsf(pwmp[i])){
			tmp1=fabsf(pwmp[i]);
		}
	}
	for(int i=0;i<=2;i++){
		pwmp[i]=pwmp[i]/tmp1;
	}
	cw0.digitalWrite(0);
	ccw0.digitalWrite(1);
	cw1.digitalWrite(0);
	ccw1.digitalWrite(1);
	cw2.digitalWrite(0);
	ccw2.digitalWrite(1);

	for(int i=0;i<=2;i++){
		if(pwmp[i]<0){
			if(i==0){
				cw0.digitalWrite(1);
				ccw0.digitalWrite(0);
				pwmp[i]=pwmp[i]*-1;
			}
			if(i==1){
				cw1.digitalWrite(1);
				ccw1.digitalWrite(0);
				pwmp[i]=pwmp[i]*-1;
			}
			if(i==2){
				cw2.digitalWrite(1);
				ccw2.digitalWrite(0);
				pwmp[i]=pwmp[i]*-1;
			}
		}
	}



	if(distance<=5){
		for(int i=0;i<=2;i++){
			pwmp[i]=pwmp[i]*distance/5.0;
		}
	}

}
