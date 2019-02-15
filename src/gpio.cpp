#include "gpio.h"

GPIO::~GPIO(){std::cout << "GPIO destructor" << std::endl;}

void GPIO::create_gpio(std::string x) { this->gpionum = x; }

int GPIO::export_gpio() {
  std::string export_str = "/sys/class/gpio/export";
  std::ofstream exportgpio(export_str.c_str());
  exportgpio << this->gpionum;
  exportgpio.close();
  return 0;
}

int GPIO::unexport_gpio() {
  std::string unexport_str = "/sys/class/gpio/unexport";
  std::ofstream unexportgpio(unexport_str.c_str());
  unexportgpio << this->gpionum;
  unexportgpio.close();
  return 0;
}

int GPIO::setdir_gpio(std::string dir) {
  std::string setdir_str ="/sys/class/gpio/gpio" + this->gpionum + "/direction";
  std::ofstream setdirgpio(setdir_str.c_str());
  setdirgpio << dir;
  setdirgpio.close();
  return 0;
}

int GPIO::setval_gpio(std::string val) {
  std::string setval_str = "/sys/class/gpio/gpio" + this->gpionum + "/value";
  std::ofstream setvalgpio(setval_str.c_str());
  setvalgpio << val;
  setvalgpio.close();
  return 0;
}

int GPIO::getval_gpio(std::string &val) {
  std::string getval_str = "/sys/class/gpio/gpio" + this->gpionum + "/value";
  std::ifstream getvalgpio(getval_str.c_str());
  getvalgpio >> val;
  if (val != "0")
    val = "1";
  else
    val = "0";
  getvalgpio.close();
  return 0;
}

std::string GPIO::get_gpionum() { return this->gpionum; }

#ifdef BUILD_INDIVIDUAL
int main(){
	return 0;
}
#endif
