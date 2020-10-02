#include <fstream>
#include <string>

#include "communication/gpio.hpp"

Gpio::Gpio(const int gpionum)
  : gpionum_(gpionum) {}

void Gpio::setGpioNum(const int gpionum) {
  gpionum_ = gpionum;
}

void Gpio::exportGpio() const {
  constexpr char export_str[] = "/sys/class/gpio/export";
  std::ofstream exportgpio(export_str);
  exportgpio << gpionum_;
  exportgpio.close();
}

void Gpio::unexportGpio() const {
  constexpr char unexport_str[] = "/sys/class/gpio/unexport";
  std::ofstream unexportgpio(unexport_str);
  unexportgpio << gpionum_;
  unexportgpio.close();
}

void Gpio::setDirGpio(const std::string& dir) {
  direction_ = dir;
  const std::string setdir_str ="/sys/class/gpio/gpio" + std::to_string(gpionum_) + "/direction";
  std::ofstream setdirgpio(setdir_str.c_str());
  setdirgpio << direction_;
  setdirgpio.close();
}

void Gpio::setValGpio(const int val) {
  val_ = val;
  const std::string setval_str = "/sys/class/gpio/gpio" + std::to_string(gpionum_) + "/value";
  std::ofstream setvalgpio(setval_str.c_str());
  setvalgpio << val_;
  setvalgpio.close();
}

int Gpio::readValGpio() const {
  int val;
  const std::string getval_str = "/sys/class/gpio/gpio" + std::to_string(gpionum_) + "/value";
  std::ifstream getvalgpio(getval_str.c_str());
  getvalgpio >> val;
  getvalgpio.close();
  return val;
}

int Gpio::getValGpio() const {
  return val_;
}

int Gpio::getGpioNum() const {
  return gpionum_;
}

std::string Gpio::getDirGpio() const {
  return direction_;
}
