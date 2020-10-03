#include <chrono>
#include <thread>

#include "communication/LegacyGpio.hpp"
#include "communication/SafeLegacyGpio.hpp"
#include "communication/i2c.hpp"
#include "communication/pwm.hpp"
#include "communication/serial.hpp"
#include "communication/utils.hpp"

int main(){
  PWM p(0);
  p.exportPwm();
  p.setPolarityPwm("normal");
  p.setPeriodPwm(100000);
  p.setDutyCyclePwm(200000);
  p.enablePwm();

	std::this_thread::sleep_for(std::chrono::seconds(100));

  p.disablePwm();
  p.unexportPwm();

  return EXIT_SUCCESS;
}
