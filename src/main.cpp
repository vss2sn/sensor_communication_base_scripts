/*
Please make sure BUILD_INDIVIDUAL is set to "OFF" if building this file.
*/

#include "main.h"
#include "gpio.h"
#include "i2c.h"
#include "pwm.h"
#include "serial.h"
#include "threading.h"
#include "utils.h"

int main(){
	int i=0;
	while(true){
		LogDebug() << i;
		i+=1;
		usleep(1000000);
	}
	return 0;
}
