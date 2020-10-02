/*******************************************************************************
 PWM common functions
*******************************************************************************/
#include <fstream>
#include <iostream>
#include <string>

#include "communication/pwm.hpp"

PWM::PWM(const int chip_num) : chip_num_(chip_num) {}

void PWM::exportPwm() {
  const std::string export_str = "/sys/class/pwm/pwmchip" + std::to_string(chip_num_) + "/export";
  std::ofstream exportpwm(export_str.c_str());
  exportpwm << "0";
  exportpwm.close();
}

void PWM::unexportPwm() {
  const std::string unexport_str = "/sys/class/pwm/pwmchip" + std::to_string(chip_num_) +
			     "/export";
  std::ofstream unexportpwm(unexport_str.c_str());
  unexportpwm << "0";
  unexportpwm.close();
}

void PWM::setPeriodPwm(const int period) {
  period_ = period;
  const std::string export_str = "/sys/class/pwm/pwmchip" + std::to_string(chip_num_) +
			   "/pwm" + std::to_string(chip_num_) +
			   "/period";
  std::ofstream period_pwm(export_str.c_str());
  period_pwm << period_;
  period_pwm.close();
}

void PWM::setDutyCyclePwm(const int duty_cycle) {
  duty_cycle_ = duty_cycle;
  const std::string export_str = "/sys/class/pwm/pwmchip" + std::to_string(chip_num_) +
                           "/pwm" + std::to_string(chip_num_) +
                           "/duty_cycle";
  std::ofstream duty_cycle_pwm(export_str.c_str());
  duty_cycle_pwm << duty_cycle_;
  duty_cycle_pwm.close();
}

void PWM::enablePwm(const std::string& tag) {
  const std::string export_str = "/sys/class/pwm/pwmchip" + std::to_string(chip_num_) +
                           "/pwm" + std::to_string(chip_num_) +
                           "/enable";
  std::ofstream enable_pwm(export_str.c_str());
  enable_pwm << tag;
  enable_pwm.close();
}

void PWM::disablePwm() {
  const std::string export_str = "/sys/class/pwm/pwmchip" + std::to_string(chip_num_) +
                           "/pwm" + std::to_string(chip_num_) +
                           "/enable";
  std::ofstream disable_pwm(export_str.c_str());
  disable_pwm << "0";
  disable_pwm.close();
}

void PWM::setPolarityPwm(const std::string& polarity) {
  polarity_ = polarity;
  const std::string polarity_str = "/sys/class/pwm/pwmchip" + std::to_string(chip_num_) +
		 	   "/pwm" + std::to_string(chip_num_) +
			   "/polarity";
  std::ofstream polarity_pwm(polarity_str.c_str());
  polarity_pwm << polarity_; //change to inverse if reading
  polarity_pwm.close();
}

void PWM::setChipNum(const int chip_num) {
  chip_num_ = chip_num;
}

#ifdef BUILD_INDIVIDUAL
int main(){
	return 0;
}
#endif
