#include <cstring>
#include <fstream>
#include <fcntl.h> // for O_RDWR
#include <iostream>
#include <string>
#include <string.h> // for strerror
#include <termios.h>
#include <unistd.h>


#include "communication/Serial.hpp"

int Serial::setInterfaceAttribs(int fd, int speed, int parity) {
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

void Serial::setBlocking(int fd, int should_block) {
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

bool Serial::openDevice() {
  fd = open(dev.c_str(), O_RDWR | O_NOCTTY | O_SYNC);
  if (fd < 0) {
    std::cout << "error opening " << dev << ": " << strerror(errno) << std::endl;
    return false;
  }
  std::cout << "Device opened as: " << fd << std::endl;
  usleep(500000);
  setInterfaceAttribs(fd, (speed_t)B9600, 0);
  return true;
}

int Serial::writeString(const std::string& tag) {
  return write(fd, &tag[0], strlen(&tag[0]));
}

int Serial::readWithTimout() {
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

std::string Serial::readStringWithTimout() {
  int n = 0;
  n = readWithTimout();
  std::string response = reinterpret_cast<const char *>(readbuf);
  memset(&readbuf[0], 0, sizeof(readbuf));
  return response;
}
