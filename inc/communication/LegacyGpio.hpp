#include <string>

class LegacyGpio {
public:
  LegacyGpio(const int gpionum);
  void setGpioNum(const int gpionum);
  void exportGpio() const;
  void unexportGpio() const;
  void setDirGpio(const std::string& dir);
  void setValGpio(const int val);
  int getValGpio();
  int getGpioNum() const;
  int getValGpio() const;
  int readValGpio() const;
  std::string getDirGpio() const;
private:
  int gpionum_;
  int val_;
  std::string direction_;
};
