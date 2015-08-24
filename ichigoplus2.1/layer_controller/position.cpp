#include "position.hpp"

void Position::radian(){
	encf[0]=canEncC0->count();//0->1
	encf[1]=canEncC1->count();
	encf[2]=canEncC2->count();
/*
	for(int i=0;i<=2;i++){
		if(encf[i]-oldEnc[i]>=50000){
			encDivietion[i]=encf[i]-oldEnc[i];
		}
	}
	*/

	for(int i=0;i<=2;i++){
		oldEnc[i]=encf[i];
	}

	for(int i=0;i<=2;i++){
		oldEncDistance[i]=encDistance[i];
	}
	if(sw3.digitalRead()==0){
		for(int i=0;i<=2;i++){
			encDivietion[i]=encf[i];
		}
	}
	encDistance[0]=diameter*M_PI*(encf[0]-encDivietion[0])/1000.0;
	encDistance[2]=diameter*M_PI*(encf[2]-encDivietion[2])/200.0;
	encDistance[1]=diameter*M_PI*(encf[1]-encDivietion[1])/200.0;

	for(int i=0;i<=2;i++){
		newEncDistance[i]=encDistance[i]-oldEncDistance[i];
	}

	rad=(encDistance[0]+encDistance[1]+encDistance[2])/(l*3.0);
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

void Position::selfPosition(){
	firstY=((newEncDistance[0]+newEncDistance[1])/(2*cos(M_PI/6.0)))-newEncDistance[0]/cos(M_PI/6.0);
	secondY=-tan(M_PI/6.0)*newEncDistance[2]-(newEncDistance[0]/cos(M_PI/6.0));
	thirdY=tan(M_PI/6.0)*newEncDistance[2]+(newEncDistance[1]/cos(M_PI/6.0));

	firstX=(newEncDistance[0]+newEncDistance[1])/(2*cos(M_PI/6.0)*tan(M_PI/6.0));
	secondX=-newEncDistance[2];
	thirdX=-newEncDistance[2];

	x=(firstX+secondX+thirdX)/3.0;
	y=(firstY+secondY+thirdY)/3.0;

	integralx+=x*cos(rad)-y*sin(rad);
	integraly+=y*cos(rad)+x*sin(rad);
	return;
}
