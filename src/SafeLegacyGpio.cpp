#include <optional>
#include <mutex>
#include <string>
#include <vector>
#include <fstream>

#include "communication/SafeLegacyGpio.hpp"

SafeLegacyGpio::SafeLegacyGpio(const int pin_num, const int val, const std::string& direction){
  std::lock_guard<std::recursive_mutex> lock(m_);
  if(!checkAnyPinHeld(pin_num)) {
    setPin(pin_num);
    setPinDir(direction);
    setPinVal(val);
  }
}

bool SafeLegacyGpio::checkAnyPinHeld(const int pin_num){
  std::lock_guard<std::recursive_mutex> lock(m_);
  if(pins_in_use_.find(pin_num) == pins_in_use_.end()) {
    return false;
  } else {
    return true;
  }
}

std::optional<int> SafeLegacyGpio::getAnyPinVal(const int pin_num){
  std::lock_guard<std::recursive_mutex> lock(m_);
  if(pins_in_use_.find(pin_num) == pins_in_use_.end()) {
    return std::nullopt;
  } else {
    int val;
    const std::string getval_str = "/sys/class/gpio/gpio" + std::to_string(pin_num) + "/value";
    std::ifstream getvalgpio(getval_str.c_str());
    getvalgpio >> val;
    getvalgpio.close();
    return val;
  }
}

std::optional<std::string> SafeLegacyGpio::getAnyPinDirection(const int pin_num){
  std::lock_guard<std::recursive_mutex> lock(m_);
  if(pins_in_use_.find(pin_num) == pins_in_use_.end()) {
    return std::nullopt;
  } else {
    std::string direction;
    const std::string setdir_str ="/sys/class/gpio/gpio" + std::to_string(pin_num) + "/direction";
    std::ifstream setdirgpio(setdir_str.c_str());
    setdirgpio >> direction;
    setdirgpio.close();
    return direction;
  }
}

bool SafeLegacyGpio::checkifPinHeld() const {
  return pin_held_;
}

std::optional<int> SafeLegacyGpio::getPinNumber() const {
  if(pin_held_) {
    return pin_num_;
  } else {
    return std::nullopt;
  }
}

// bool SafeLegacyGpio::requestPinWithTimeout(const int pin_num){}

bool SafeLegacyGpio::requestPin(const int pin_num, const int val, const std::string& direction) {
  std::lock_guard<std::recursive_mutex> lock(m_);
  if(pin_num == pin_num_) { // already holding requested pin
    return true;
  } else if (checkAnyPinHeld(pin_num)) { // requestd pin already in use
    return false;
  } else if (pin_held_) { // holding another pin and requested pin is free
    unsetPin();
    setPin(pin_num);
    setPinDir(direction);
    setPinVal(val);
    return true;
  } else { // requested pin is free
    setPin(pin_num);
    setPinDir(direction);
    setPinVal(val);
    return true;
  }
}

std::optional<int> SafeLegacyGpio::getPinVal() const {
  if(pin_held_) {
    return val_;
  } else {
    return std::nullopt;
  }
}

bool SafeLegacyGpio::setPinVal(const int val) {
  if(pin_held_) {
    setPinValHelper(val);
    return true;
  } else {
    return false;
  }
}
//
// std::optional<int> SafeLegacyGpio::setPinVal(const int val) const {
//   if(pin_held_) {
//     return readPinValHelper(val);
//   } else {
//     return std::nullopt;
//   }
// }


std::optional<std::string> SafeLegacyGpio::getPinDir() const {
  if(pin_held_) {
    return dir_;
  } else {
    return std::nullopt;
  }
}

bool SafeLegacyGpio::setPinDir(const std::string& dir){
  if(pin_held_) {
    setPinDirHelper(dir);
    return true;
  } else {
    return false;
  }
}

SafeLegacyGpio::~SafeLegacyGpio(){
  std::lock_guard<std::recursive_mutex> lock(m_);
  unsetPin();
};

void SafeLegacyGpio::setPinDirHelper(const std::string& dir) {
  dir_ = dir;
  const std::string setdir_str ="/sys/class/gpio/gpio" + std::to_string(pin_num_) + "/direction";
  std::ofstream setdirgpio(setdir_str.c_str());
  setdirgpio << dir_;
  setdirgpio.close();
};

void SafeLegacyGpio::setPinValHelper(const int val) {
  val_ = val;
  const std::string setval_str = "/sys/class/gpio/gpio" + std::to_string(pin_num_) + "/value";
  std::ofstream setvalgpio(setval_str.c_str());
  setvalgpio << val_;
  setvalgpio.close();
};

void SafeLegacyGpio::exportPin() const {
  constexpr char export_str[] = "/sys/class/gpio/export";
  std::ofstream exportgpio(export_str);
  exportgpio << pin_num_;
  exportgpio.close();
}

void SafeLegacyGpio::unexportPin() const {
  constexpr char unexport_str[] = "/sys/class/gpio/unexport";
  std::ofstream unexportgpio(unexport_str);
  unexportgpio << pin_num_;
  unexportgpio.close();
}

int SafeLegacyGpio::readPinValHelper() const {
  int val;
  const std::string getval_str = "/sys/class/gpio/gpio" + std::to_string(pin_num_) + "/value";
  std::ifstream getvalgpio(getval_str.c_str());
  getvalgpio >> val;
  getvalgpio.close();
  return val;
}

void SafeLegacyGpio::setPin(const int pin_num) {
  pin_num_ = pin_num;
  pins_in_use_.insert(pin_num);
  pin_held_ = true;
  exportPin();
}

void SafeLegacyGpio::unsetPin() {
  unexportPin();
  pin_held_ = false;
  pins_in_use_.erase(pin_num_);
}
