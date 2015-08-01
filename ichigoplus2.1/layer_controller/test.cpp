#include "test.hpp"

void Testmotor::motortest(){
	pwm0.pwmWrite(0);
	pwm1.pwmWrite(0);
	pwm2.pwmWrite(0);
	cw0.digitalWrite(0);
	ccw0.digitalWrite(1);
	cw1.digitalWrite(0);
	ccw1.digitalWrite(1);
	cw2.digitalWrite(0);
	ccw2.digitalWrite(1);
	b=millis();

	serial.printf("%d,%d,%d,%d\n\r",enc0.count(),enc1.count(),enc2.count(),b);
	return;
}
