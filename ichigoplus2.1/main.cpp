//libraries
#include <math.h>

//application

//controller

//base
#include "system.h"
#include "mcutime.h"

//board
#include "pin.hpp"

//circuit
class Three{
    public:
		float xPurpose[10]{250,0,-250,0,250,-250,250,-250,0,0};//x
		float yPurpose[10]{250,500,250,0,0,500,500,0,0};//y
		float pwmp[3]={1,1,1};
		float oed[3]={0,0,0};
		float pwmLock[3]={0,0,0};
		float ned[3]={0,0,0};
		float encDistance[3]={0,0,0};
		float encf[3]{0,0,0};
        float rad=0;
        float degree=0;
        float degreeOld=0;
        float deg=0;
        float dControl=0;
        float oldEnc0=0;
        float oldEnc1=0;
        float oldEnc2=0;
        float integralx=0;
        float integraly=0;
        float distance=0;
        float odis=0;
        float mokux=0;
        float mokuy=0;
        float tmp=0;
        float tmp1=0;
        float x=0;
        float y=0;
		float firstX=0;
		float secondX=0;
		float thirdX=0;
		float firstY=0;
		float secondY=0;
		float thirdY=0;
		int sw=0;
        int time=0;
		int divide=0;
		int k=0;

		#define l 90//enc distance from the center
    	#define pGain 1.0/180.0	//p gain
		#define dGain 0.6		//d gain
		#define	diameter 40

        Serial0 serial;
        CCW0 ccw0;
        CCW1 ccw1;
        CCW2 ccw2;
        CW0 cw0;
        CW1 cw1;
        CW2 cw2;
        Pwm0 pwm0;
        Pwm1 pwm1;
        Pwm2 pwm2;
        Enc0 enc0;
        Enc1 enc1;
        Enc2 enc2;
        Sw0 sw0;
        Sw1 sw1;

        Three();
        void degree1();
        void selfPosition();
        void degreeLock();
        void test();
        void xy();
        void motorControl();
        void final();
        void indication();
        void switch0();
};

Three::Three(){
	ccw0.setupDigitalOut();
	ccw1.setupDigitalOut();
	ccw2.setupDigitalOut();

	cw0.setupDigitalOut();
	cw1.setupDigitalOut();
	cw2.setupDigitalOut();

	pwm0.setupPwmOut(100000,1.0);
	pwm1.setupPwmOut(100000,1.0);
	pwm2.setupPwmOut(100000,1.0);

	serial.setup(115200);
	enc0.setup();
	enc1.setup();
	enc2.setup();
	sw0.setupDigitalIn();
//	sw1.setupDigitalIn();
}

void Three::switch0(){
	if(sw0.digitalRead()==0&&sw==0){
		sw=1;
		time=millis();
		return;
	}
	else if(sw0.digitalRead()==0&&sw==1){
		sw=0;
		pwm0.pwmWrite(1);
		pwm1.pwmWrite(1);
		pwm2.pwmWrite(1);
		cw0.digitalWrite(0);
		ccw0.digitalWrite(0);
		cw1.digitalWrite(0);
		ccw1.digitalWrite(0);
		cw2.digitalWrite(0);
		ccw2.digitalWrite(0);
		return;
	}
}
void Three::xy(){
	if(distance<=1.0&&k!=9){
		k++;
	}
	return;
}

void Three::degree1(){
	encf[0]=enc0.count();
	encf[1]=enc1.count();
	encf[2]=enc2.count();

	for(int i=0;i<=2;i++){
		oed[i]=encDistance[i];
	}

	for(int i=0;i<=2;i++){
		encDistance[i]=diameter*M_PI*encf[i]/200.0;
	}

	for(int i=0;i<=2;i++){
		ned[i]=encDistance[i]-oed[i];
	}

	rad=(encDistance[0]+encDistance[1]+encDistance[2])/(l*3);
	degree=rad/M_PI*180;

	divide=degree/180;
	if(divide>0){
		if(divide%2!=0){
			divide++;
		}
		degree=degree-180*divide;
	}
	if(divide<0){
		if(divide%2!=0){
			divide--;
		}
		degree=degree-180*divide;
	}
	if((int)degree%180==0&&divide%2!=0){
		degree=180;
	}
	return;
}

void Three::selfPosition(){
	firstY=((ned[1]+ned[2])/(2*cos(30*M_PI/180)))-ned[1]/cos(30*M_PI/180);
	secondY=-tan(30*M_PI/180)*ned[0]-(ned[1]/cos(30*M_PI/180));
	thirdY=tan(30*M_PI/180)*ned[0]+(ned[2]/cos(30*M_PI/180));

	firstX=(ned[1]+ned[2])/(2*cos(30*M_PI/180)*tan(30*M_PI/180));
	secondX=-ned[0];
	thirdX=-ned[0];

	x=(firstX+secondX+thirdX)/3.0;
	y=(firstY+secondY+thirdY)/3.0;

	integralx+=x*cos(rad)-y*sin(rad);
	integraly+=y*cos(rad)+x*sin(rad);

	mokux=xPurpose[k]-integralx;
	mokuy=yPurpose[k]-integraly;

	distance=hypotf(mokuy,mokux);
	return;
}

void Three::motorControl(){
	deg=atan2f(mokuy,mokux);
	pwmp[1]=-1*sin(deg-30*M_PI/180);
	pwmp[0]=-1*cos(deg);
	pwmp[2]=sin(30*M_PI/180+deg);

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

void Three::degreeLock(){
	dControl+=(degree-degreeOld)*dGain;
	for(int i=0;i<=2;i++){
		pwmLock[i]=degree*pGain+dControl;
	}

	for(int i=0;i<=2;i++){
		pwmLock[i]=pwmLock[i]/3.0;
	}

	degreeOld=degree;
	return;
}

void  Three::final(){

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

	tmp1=fabsf(pwmp[0]);

	for(int i=1;i<=2;i++){
		if(tmp1<fabsf(pwmp[i])){
			tmp1=fabsf(pwmp[i]);
		}
	}

	for(int i=0;i<=2;i++){
		pwmp[i]=pwmp[i]/fabsf(tmp1);
	}

	for(int i=0;i<=2;i++){
		pwmp[i]=1-pwmp[i];
	}

	pwm0.pwmWrite(pwmp[0]);
	pwm1.pwmWrite(pwmp[1]);
	pwm2.pwmWrite(pwmp[2]);
	return;

}


void Three::indication(){
	serial.printf("\r%.2f,%.2f,%.2f,%d,%d,%d,%.2f,%.2f,%.2f\n",degree,integralx,integraly,enc0.count(),enc1.count(),enc2.count(),pwmp[0],pwmp[1],pwmp[2]);
	return;
}

void Three::test(){


	for(int i=0;i<=2;i++){
		pwmp[i]=0;

		pwm0.pwmWrite(pwmp[0]);
		pwm1.pwmWrite(pwmp[1]);
		pwm2.pwmWrite(pwmp[2]);
		cw0.digitalWrite(0);
		ccw0.digitalWrite(1);
		cw1.digitalWrite(0);
		ccw1.digitalWrite(1);
		cw2.digitalWrite(0);
		ccw2.digitalWrite(1);
		wait(1000);


	serial.printf("%d,%d,%d\n\r",enc0.count(),enc1.count(),enc2.count());
	}
	return;

}
int main(){
	Three t;
	while(1){

		if(t.sw==0){
			t.switch0();
		}

		if(t.sw==1){
			t.degree1();
			t.selfPosition();
			t.xy();
			t.motorControl();
			t.degreeLock();
			t.final();
			t.indication();

			if(millis()-t.time>500){
				t.switch0();
			}
		}
	//t.test();
	}
	return 0;
}
