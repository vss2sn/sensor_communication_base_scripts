#include <string>

#include <linux/i2c-dev.h>

class I2C{
public:

	I2C(const std::string& dev, const int slave_addr);
	bool openDevice();

	void setDevice(const std::string& dev);
	void setSlaveAddr(const int slave_addr);

	bool checkI2c();

	bool readI2c(char* buffer, std::size_t length);
	bool writeI2c(char* buffer, std::size_t length);
	
private:
	std::string dev_; 	// Device
	int fd_;
	int slave_addr_; // Slave address
};
