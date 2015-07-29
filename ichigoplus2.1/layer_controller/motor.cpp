#include "motor.hpp"

Motor::Motor(){
	ccw0.setupDigitalOut();
	ccw1.setupDigitalOut();
	ccw2.setupDigitalOut();

	cw0.setupDigitalOut();
	cw1.setupDigitalOut();
	cw2.setupDigitalOut();

	pwm0.setupPwmOut(100000,1.0);
	pwm1.setupPwmOut(100000,1.0);
	pwm2.setupPwmOut(100000,1.0);
}
void Motor::motorControl(float& mokuxC,float& mokuyC){
	deg=atan2f(mokuyC,mokuxC);
	distance=hypot(mokuxC,mokuyC);
	pwmp[0]=sin(deg-M_PI/6.0);
	pwmp[2]=cos(deg);
	pwmp[1]=-1*sin(M_PI/6.0+deg);

	tmp=fabsf(pwmp[0]);

	for(int i=1;i<=2;i++){
		if(tmp<fabsf(pwmp[i])){
			tmp=fabsf(pwmp[i]);
		}
	}
	for(int i=0;i<=2;i++){
		pwmp[i]=pwmp[i]/fabsf(tmp);
	}

	return;
}

void Motor::degreeLock(float& degree1){
	dControl+=(degree1-degreeOld)*dGain;
	for(int i=0;i<=2;i++){
		pwmLock[i]=degree1*pGain+dControl;
	}

	for(int i=0;i<=2;i++){
		pwmLock[i]=pwmLock[i]/2.5;
	}
	degreeOld=degree1;
	return;
}

void Motor::dutyCleanUp(){

	tmp1=fabsf(pwmp[0]);

	for(int i=1;i<=2;i++){
		if(tmp1<fabsf(pwmp[i])){
			tmp1=fabsf(pwmp[i]);
		}
	}

	for(int i=0;i<=2;i++){
		pwmp[i]=pwmp[i]/fabsf(tmp1);
	}


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
		pwmp[i]=pwmp[i]/fabsf(tmp1);
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

	if(distance<=100){
		for(int i=0;i<=2;i++){
			pwmp[i]=pwmp[i]*(distance/100.0);
		}
	}
}
