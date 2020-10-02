#include <chrono>
#include <thread>

#include "communication/gpio.hpp"
#include "communication/i2c.hpp"
#include "communication/pwm.hpp"
#include "communication/serial.hpp"
#include "communication/utils.hpp"

int main(){
	while(true){
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	return 0;
}
