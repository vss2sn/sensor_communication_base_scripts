/*******************************************************************************
 PWM common functions
*******************************************************************************/
#include "pwm.h"

int PWM::export_pwm() {
  std::string export_str = "/sys/class/pwm/pwmchip" + std::to_string(pwm_chip_num) + "/export";
  std::ofstream exportpwm(export_str.c_str());
  exportpwm << "0";
  exportpwm.close();
  return 0;
}

int PWM::unexport_pwm() {
  std::string unexport_str = "/sys/class/pwm/pwmchip" + std::to_string(pwm_chip_num) +
			     "/export";
  std::ofstream unexportpwm(unexport_str.c_str());
  unexportpwm << "0";
  unexportpwm.close();
  return 0;
}

int PWM::set_period_pwm() {
  std::string export_str = "/sys/class/pwm/pwmchip" + std::to_string(pwm_chip_num) +
			   "/pwm" + std::to_string(pwm_chip_num) +
			   "/period";
  std::ofstream period_pwm(
      export_str.c_str());
  period_pwm << pwm_period;
  period_pwm.close();
  return 0;
}

int PWM::set_duty_cycle_pwm() {
  std::string export_str = "/sys/class/pwm/pwmchip" + std::to_string(pwm_chip_num) +
                           "/pwm" + std::to_string(pwm_chip_num) +
                           "/duty_cycle"; //"/pwm"+std::to_string(number)+"/polarity"
  std::ofstream duty_cycle_pwm(
      export_str.c_str());
  duty_cycle_pwm << pwm_duty_cycle;
  duty_cycle_pwm.close();
  return 0;
}

int PWM::enable_pwm(std::string tag) {
  std::string export_str = "/sys/class/pwm/pwmchip" + std::to_string(pwm_chip_num) +
                           "/pwm" + std::to_string(pwm_chip_num) +
                           "/enable"; //"/pwm"+std::to_string(number)+"/polarity"
  std::ofstream enable_pwm(
      export_str.c_str());
  enable_pwm << tag;
  enable_pwm.close();
  return 0;
}

int PWM::disable_pwm() {
  std::string export_str = "/sys/class/pwm/pwmchip" + std::to_string(pwm_chip_num) +
                           "/pwm" + std::to_string(pwm_chip_num) +
                           "/enable"; //"/pwm"+std::to_string(number)+"/polarity"
  std::ofstream disable_pwm(
      export_str.c_str());
  disable_pwm << "0";
  disable_pwm.close();
  return 0;
}

int PWM::set_polarity_pwm(std::string tag) {
  std::string polarity_str = "/sys/class/pwm/pwmchip" + std::to_string(pwm_chip_num) +
		 	   "/pwm" + std::to_string(pwm_chip_num) +
			   "/polarity";
  std::ofstream polarity_pwm(polarity_str.c_str());
  polarity_pwm << tag; //change to inverse if reading
  polarity_pwm.close();
  return 0;
}

// NOTE: Not using constructor as this allows alterations to settings on the fly before setting pin to enable.
//TODO: create wrapper
int PWM::create_pwm() {
  export_pwm();
  set_period_pwm();
  set_duty_cycle_pwm();
  enable_pwm();
  return 0;
}

void PWM::set_val(std::string tag) {
  // NOTE: this can be used directly to set the duty cycle as a percentage of
  // the pulse or in microsceonds. Make sure pwm_duty_cycle is always less then
  // the pwm_period or it will not work.
  int number = stoi(tag);
  pwm_duty_cycle = number;
  set_duty_cycle_pwm();
}
void PWM::set_default() {
  pwm_duty_cycle = default_pwm_duty_cycle;
  set_duty_cycle_pwm();
}

#ifdef BUILD_INDIVIDUAL
int main(){
	return 0;
}
#endif
