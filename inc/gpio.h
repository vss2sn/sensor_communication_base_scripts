#include "main.h"
class GPIO{
protected:
  std::string gpionum;
public:
  GPIO();
  ~GPIO();
  void create_gpio(std::string x);
  int export_gpio();
  int unexport_gpio();
  int setdir_gpio(std::string dir);
  int setval_gpio(std::string val);
  int getval_gpio(std::string &val);
  std::string get_gpionum();
};
