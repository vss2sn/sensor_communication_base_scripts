#include <string>

class PWM {
private:
  int chip_num_ = 0;
  int period_ = 0;
  int duty_cycle_ = 0;
  std::string polarity_;
public:
    PWM(const int);
    void createPwm();
    void exportPwm();
    void unexportPwm();
    void setPeriodPwm(const int period);
    void setDutyCyclePwm(const int duty_cycle);
    void setPolarityPwm(const std::string& tag = "normal");
    void enablePwm(const std::string& polarity);
    void disablePwm();
    void setChipNum(const int chip_num);
};
