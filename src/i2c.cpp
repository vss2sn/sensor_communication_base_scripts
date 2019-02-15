/*
References:
https://www.kernel.org/doc/Documentation/i2c/dev-interfac
*/

#include "i2c.h"

I2C::I2C(){
	/*
	If reading from another file / manually setting, set here
	*/
	fd = open(dev.c_str(), O_RDWR | O_NOCTTY | O_SYNC);
	if (fd < 0){
		std::cout << "Error opening " << dev << ":" << strerror(errno) << std::endl;;
	}
}

bool I2C::check_i2c(){
	if(ioctl(fd, I2C_SLAVE, slave_addr) < 0){
		std::cout << "Failed to aquire bus access or talk to slave" << std::endl;;
		return false;
	}
	return true;
}

bool I2C::read_i2c(){
	op_n = read(fd, buffer, length);
	if(op_n !=length){
		std::cout << "Failed to read expected number of bytes. Read " << op_n << " instead of " << length << std::endl;
		std::cout << "Read: " << buffer << std::endl;
		return false;
	}
	return true;
}

bool I2C::write_i2c(std::string tag){
	length = tag.length();
	op_n = write(fd, tag.c_str(), length);
	if (op_n!=length){
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
