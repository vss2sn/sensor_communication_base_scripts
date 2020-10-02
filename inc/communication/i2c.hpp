/*******************************************************************************
I2C
*******************************************************************************/
#include <string>

#include <linux/i2c-dev.h>

class I2C{
	std::string dev_; 	// Device
	int fd;
	int slave_addr; // Slave address
	int buffer_size;
	char buffer[255];  // Buffer ot store read values
	int op_n;   // Number of actual bytes in read/write operation
public:
	I2C(const std::string& dev);
	bool openDevice();
	void setDevice(const std::string& dev);
	bool checkI2c();
	std::tuple<bool, std::string> readI2c(const int n_bytes);
	bool writeI2c(const std::string& tag);
};
