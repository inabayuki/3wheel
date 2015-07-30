#include "position.hpp"




void Position::radian(){
	encf[2]=canEncC0->count();//0->1
	encf[0]=canEncC1->count();
	encf[1]=canEncC2->count();

	for(int i=0;i<=2;i++){
		oldEncDistance[i]=encDistance[i];
	}

	for(int i=0;i<=2;i++){
		encDistance[i]=diameter*M_PI*encf[i]/200.0;
	}

	for(int i=0;i<=2;i++){
		newEncDistance[i]=encDistance[i]-oldEncDistance[i];
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

void Position::selfPosition(){
	firstY=((newEncDistance[1]+newEncDistance[2])/(2*cos(M_PI/6.0)))-newEncDistance[1]/cos(M_PI/6.0);
	secondY=-tan(M_PI/6.0)*newEncDistance[0]-(newEncDistance[1]/cos(M_PI/6.0));
	thirdY=tan(M_PI/6.0)*newEncDistance[0]+(newEncDistance[2]/cos(M_PI/6.0));

	firstX=(newEncDistance[1]+newEncDistance[2])/(2*cos(M_PI/6.0)*tan(M_PI/6.0));
	secondX=-newEncDistance[0];
	thirdX=-newEncDistance[0];

	x=(firstX+secondX+thirdX)/3.0;
	y=(firstY+secondY+thirdY)/3.0;

	integralx+=x*cos(rad)-y*sin(rad);
	integraly+=y*cos(rad)+x*sin(rad);
	return;
}
