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

I2C::I2C(const std::string& dev)
	: dev_(dev) {
		buffer_size = strlen(buffer);
	}

bool I2C::openDevice() {
	fd = open(dev_.c_str(), O_RDWR | O_NOCTTY | O_SYNC);
	if (fd < 0){
		std::cout << "Error opening " << dev_ << ":" << strerror(errno) << std::endl;
		return false;
	} else {
		return true;
	}
}

void I2C::setDevice(const std::string& dev) {
	dev_ = dev;
}

bool I2C::checkI2c(){
	if(ioctl(fd, I2C_SLAVE, slave_addr) < 0){
		std::cout << "Failed to aquire bus access or talk to slave" << std::endl;;
		return false;
	}
	return true;
}

std::tuple<bool, std::string> I2C::readI2c(const int n_bytes){
	if(n_bytes > buffer_size) {
		std::cout << "Failed to read expected number of bytes" << std::endl;
		// return {false, std::string()};
	}

	op_n = read(fd, buffer, n_bytes);
	std::string read_buffer(buffer);
	read_buffer.erase(n_bytes-1, std::string::npos);
	if(op_n != n_bytes){
		std::cout << "Failed to read expected number of bytes. Read " << op_n << " instead of " << n_bytes << std::endl;
		std::cout << "Read: " << read_buffer << std::endl;
		// return {false, std::string()};
	}
	return {true, read_buffer};
}

bool I2C::writeI2c(const std::string& tag){
	const int length = tag.length();
	op_n = write(fd, tag.c_str(), length);
	if (op_n != length){
		std::cout << "Failed to write expected number of bytes. Wrote " << op_n << " instead of " << length << std::endl;
		return false;
	}
	return true;
}

#ifdef BUILD_INDIVIDUAL
int main(){
	return 0;
}
#endif
