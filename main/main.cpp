/*
Please make sure BUILD_INDIVIDUAL is set to "OFF" if building this file.
*/

#include "communication/gpio.hpp"
#include "communication/i2c.hpp"
#include "communication/pwm.hpp"
#include "communication/serial.hpp"
#include "communication/utils.hpp"

int main(){
	int i=0;
	while(true){
		LogDebug() << i;
		i+=1;
		usleep(1000000);
	}
	return 0;
}
