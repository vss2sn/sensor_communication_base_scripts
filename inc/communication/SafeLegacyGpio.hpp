#include <optional>
#include <mutex>
#include <string>
#include <unordered_set>

class SafeLegacyGpio {
public:
  SafeLegacyGpio(const int pin_num, const int val, const std::string& direction);
  ~SafeLegacyGpio();

  static bool checkAnyPinHeld(const int pin_num) ;
  static std::optional<int> getAnyPinVal(const int pin_num) ;
  static std::optional<std::string> getAnyPinDirection(const int pin_num) ;

  bool checkifPinHeld() const;
  std::optional<int> getPinNumber() const;
  // bool requestPinWithTimeout(const int pin_num);
  bool requestPin(const int pin_num, const int val, const std::string& direction);

  std::optional<int> getPinVal() const;
  bool setPinVal(const int val);
  // std::optional<int> setPinVal(const int val) const;

  std::optional<std::string> getPinDir() const;
  bool setPinDir(const std::string& dir);

private:
  static std::unordered_set<int> pins_in_use_;
  static std::recursive_mutex m_;
  int pin_num_;
  int val_;
  std::string dir_;
  bool pin_held_;

  void setPin(const int pin_num);
  void unsetPin();
  void setPinDirHelper(const std::string& dir);
  void setPinValHelper(const int val);
  void exportPin() const ;
  void unexportPin() const ;
  int readPinValHelper() const ;


};
