#include <string>

class Gpio {
public:
  Gpio(const int gpionum);
  void setGpioNum(const int gpionum);
  void exportGpio();
  void unexportGpio();
  void setDirGpio(const std::string& dir);
  void setValGpio(const int val);
  int getValGpio();
  int getGpioNum();
private:
  int gpionum_;
};
