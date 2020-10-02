/*******************************************************************************
 SERIAL common functions
*******************************************************************************/
#include "communication/serial.hpp"

SERIAL::~SERIAL(){std::cout << "SERIAL destructor" << std::endl;}

int SERIAL::set_interface_attribs(int fd, int speed, int parity) {
  struct termios tty;

  tcgetattr(fd, &tty);

  cfsetospeed(&tty, speed);
  cfsetispeed(&tty, speed);

  /* 8 bits, no parity, no stop bits */
  tty.c_cflag &= ~PARENB;
  tty.c_cflag &= ~CSTOPB;
  tty.c_cflag &= ~CSIZE;
  tty.c_cflag |= CS8;
  /* Canonical mode */
  tty.c_lflag |= ICANON;
  tcsetattr(fd, TCSANOW, &tty);

  /* Flush Port, then applies attributes */
  tcflush(fd, TCIFLUSH);
  if (tcsetattr(fd, TCSANOW, &tty) != 0) {
    std::cout << "error " << std::strerror(errno) << " from tcsetattr" << std::endl;
    return -1;
  }
  return 0;
}

void SERIAL::set_blocking(int fd, int should_block) {
  struct termios tty;
  memset(&tty, 0, sizeof tty);
  if (tcgetattr(fd, &tty) != 0) {
    std::cout << "error " << std::strerror(errno) << " from tggetattr" << std::endl;
    return;
  }

  tty.c_cc[VMIN] = should_block ? 1 : 0;
  tty.c_cc[VTIME] = 5;

  if (tcsetattr(fd, TCSANOW, &tty) != 0) {
    std::cout << "error " << std::strerror(errno) << " setting term attributes" << std::endl;
  }
}

bool SERIAL::open_device() {
  fd = open(dev.c_str(), O_RDWR | O_NOCTTY | O_SYNC);
  if (fd < 0) {
    std::cout << "error opening " << dev << ": " << strerror(errno) << std::endl;
    return false;
  }
  std::cout << "Device opened as: " << fd << std::endl;
  usleep(500000);
  set_interface_attribs(fd, (speed_t)B9600,
                        0);
  return true;
}

int SERIAL::write_string_to_serial(std::string tag) {
  return write(fd, &tag[0], strlen(&tag[0]));
}

int SERIAL::read_with_timout() {
  int n = 0;
  memset(&readbuf[0], 0, sizeof(readbuf));
  fd_set read_fds, write_fds, except_fds;
  FD_ZERO(&read_fds);
  FD_ZERO(&write_fds);
  FD_ZERO(&except_fds);
  FD_SET(fd, &read_fds);

  // Set timeout to 1.0 seconds
  struct timeval timeout;
  timeout.tv_sec = 1;
  timeout.tv_usec = 0;

  // Wait for input to become ready or until the time out; the first parameter
  // is 1 more than the largest file descriptor in any of the sets
  if (select(fd + 1, &read_fds, &write_fds, &except_fds, &timeout) == 1) {
    n = read(fd, readbuf, 100);
    tcflush(fd, TCIOFLUSH);
  } else {
    n = 0;
  }
  return n;
}

std::string SERIAL::read_string_with_timout() {
  int n = 0;
  n = read_with_timout();
  std::string response = reinterpret_cast<const char *>(readbuf);
  memset(&readbuf[0], 0, sizeof(readbuf));
  return response;
}

#ifdef BUILD_INDIVIDUAL
int main(){
	return 0;
}
#endif
