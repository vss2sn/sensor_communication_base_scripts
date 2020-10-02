/*******************************************************************************
I2C
*******************************************************************************/
#include <linux/i2c-dev.h>

class I2C{
	std::string dev="/dev/i2c-0"; 	// Device
	int fd;
	int slave_addr; // Slave address
	int length;     // Number of expected bytes in read/write operation
	char buffer[];  // Buffer ot store read values
	int op_n;   // Number of actual bytes in read/write operation
public:
	I2C();
	~I2C();
	bool check_i2c();
	bool read_i2c();
	bool write_i2c(std::string tag);
};
