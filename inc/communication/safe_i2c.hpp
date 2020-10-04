#include <unordered_set>
#include <unordered_map>

#include<string>
#include <mutex>

#include <linux/i2c-dev.h>

class SafeI2C {
public:

  SafeI2C(const std::string& dev, const int slave_addr);

	void setDevice(const std::string& dev);
  bool openDevice();

	static bool readI2c(const std::string& dev, const int slave_addr, char* buffer, const std::size_t length);
	static bool writeI2c(const std::string& dev, const int slave_addr, char* buffer, const std::size_t length);

  bool checkI2c();
  bool readI2c(char* buffer, const std::size_t length);
  bool writeI2c(char* buffer, const std::size_t length);

  bool isDeviceOpen();
  bool isSlaveCaptured();

  void setSlaveAddr(const int slave_addr);

private:

  static std::unordered_map<std::string, std::unordered_set<int>> in_use_;
  static std::recursive_mutex m_;
  static bool modified;
	std::string dev_; 	// Device
  int fd_ = -1;
  int slave_addr_;
  bool slave_captured_ = false;
  bool dev_modified = true;
};
