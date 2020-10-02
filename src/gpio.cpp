#include <string>
#include <fstream>

#include "communication/gpio.hpp"

Gpio::Gpio(const int gpionum)
  : gpionum_(gpionum) {}

void Gpio::setGpioNum(const int gpionum) {
  gpionum_ = gpionum;
}

void Gpio::exportGpio() {
  constexpr char export_str[] = "/sys/class/gpio/export";
  std::ofstream exportgpio(export_str);
  exportgpio << gpionum_;
  exportgpio.close();
}

void Gpio::unexportGpio() {
  constexpr char unexport_str[] = "/sys/class/gpio/unexport";
  std::ofstream unexportgpio(unexport_str);
  unexportgpio << gpionum_;
  unexportgpio.close();
}

void Gpio::setDirGpio(const std::string& dir) {
  const std::string setdir_str ="/sys/class/gpio/gpio" + std::to_string(gpionum_) + "/direction";
  std::ofstream setdirgpio(setdir_str.c_str());
  setdirgpio << dir;
  setdirgpio.close();
}

void Gpio::setValGpio(const int val) {
  const std::string setval_str = "/sys/class/gpio/gpio" + std::to_string(gpionum_) + "/value";
  std::ofstream setvalgpio(setval_str.c_str());
  setvalgpio << val;
  setvalgpio.close();
}

int Gpio::getValGpio() {
  int val;
  const std::string getval_str = "/sys/class/gpio/gpio" + std::to_string(gpionum_) + "/value";
  std::ifstream getvalgpio(getval_str.c_str());
  getvalgpio >> val;
  getvalgpio.close();
  return val;
}

int Gpio::getGpioNum() {
  return gpionum_;
}

#ifdef BUILD_INDIVIDUAL
int main(){
	return 0;
}
#endif
