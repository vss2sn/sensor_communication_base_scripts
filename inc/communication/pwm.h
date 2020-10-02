#include "main.h"
class PWM{
  int pwm_pin_num = 0;
  int pwm_chip_num = 0;
  int pwm_period = 0;
  int pwm_duty_cycle = 0;
  int default_pwm_duty_cycle = 0;
  int max = 170000;
  int min = 120000;


public:
    ~PWM();
    int create_pwm();
    int export_pwm();
    int unexport_pwm();
    int set_period_pwm();
    int set_duty_cycle_pwm();
    int set_polarity_pwm(std::string tag = "normal");
    int enable_pwm(std::string tag = "1");
    int disable_pwm();
    void set_val(std::string tag);
    void set_default();
};
