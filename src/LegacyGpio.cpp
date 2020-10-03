#include <fstream>
#include <string>

#include "communication/LegacyGpio.hpp"

LegacyGpio::LegacyGpio(const int gpionum)
  : gpionum_(gpionum) {}

void LegacyGpio::setGpioNum(const int gpionum) {
  gpionum_ = gpionum;
}

void LegacyGpio::exportGpio() const {
  constexpr char export_str[] = "/sys/class/gpio/export";
  std::ofstream exportgpio(export_str);
  exportgpio << gpionum_;
  exportgpio.close();
}

void LegacyGpio::unexportGpio() const {
  constexpr char unexport_str[] = "/sys/class/gpio/unexport";
  std::ofstream unexportgpio(unexport_str);
  unexportgpio << gpionum_;
  unexportgpio.close();
}

void LegacyGpio::setDirGpio(const std::string& dir) {
  direction_ = dir;
  const std::string setdir_str ="/sys/class/gpio/gpio" + std::to_string(gpionum_) + "/direction";
  std::ofstream setdirgpio(setdir_str.c_str());
  setdirgpio << direction_;
  setdirgpio.close();
}

void LegacyGpio::setValGpio(const int val) {
  val_ = val;
  const std::string setval_str = "/sys/class/gpio/gpio" + std::to_string(gpionum_) + "/value";
  std::ofstream setvalgpio(setval_str.c_str());
  setvalgpio << val_;
  setvalgpio.close();
}

int LegacyGpio::readValGpio() const {
  int val;
  const std::string getval_str = "/sys/class/gpio/gpio" + std::to_string(gpionum_) + "/value";
  std::ifstream getvalgpio(getval_str.c_str());
  getvalgpio >> val;
  getvalgpio.close();
  return val;
}

int LegacyGpio::getValGpio() const {
  return val_;
}

int LegacyGpio::getGpioNum() const {
  return gpionum_;
}

std::string LegacyGpio::getDirGpio() const {
  return direction_;
}
