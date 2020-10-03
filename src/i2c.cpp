/*
References:
https://www.kernel.org/doc/Documentation/i2c/dev-interfac
*/

#include <fcntl.h> // for O_RDWR
#include <iostream>
#include <string.h> // for strerror
#include <sys/ioctl.h> // for ioctl
#include <unistd.h> // for write
#include <string>
#include <tuple>

#include "communication/i2c.hpp"

I2C::I2C(const std::string& dev, const int slave_addr)
	: dev_(dev), slave_addr_(slave_addr) {}

bool I2C::openDevice() {
	fd_ = open(dev_.c_str(), O_RDWR | O_NOCTTY | O_SYNC);
	if(fd_ >= 0) {
		return true;
	} else {
		return false;
	}
}

void I2C::setDevice(const std::string& dev) {
	dev_ = dev;
}

void I2C::setSlaveAddr(const int slave_addr) {
	slave_addr_ = slave_addr;
}

bool I2C::checkI2c(){
	if(ioctl(fd_, I2C_SLAVE, slave_addr_) < 0){
		return false;
	} else {
		return true;
	}
}

bool I2C::readI2c(char* buffer, std::size_t length) {
	if (ioctl(fd_, I2C_SLAVE, slave_addr_) < 0) {
		return false;
	}
	if(read(fd_, buffer, length) ==  length) {
		return true;
	} else {
		return false;
	}
}

bool I2C::writeI2c(char* buffer, std::size_t length) {
	if (ioctl(fd_, I2C_SLAVE, slave_addr_) < 0) {
		return false;
	}
	if(write(fd_, buffer, length) == length) {
		return true;
	} else {
		return false;
	}
}
