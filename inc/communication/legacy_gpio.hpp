#include <string>

class LegacyGpio {
public:
  LegacyGpio(const int gpionum);

  void setGpioNum(const int gpionum);
  int getGpioNum() const;

  void exportGpio() const;
  void unexportGpio() const;

  void setDirGpio(const std::string& dir);
  std::string getDirGpio() const;

  void setValGpio(const int val);
  int getValGpio() const;

  int readValGpio() const;

private:
  int gpionum_;
  int val_;
  std::string direction_;
};
