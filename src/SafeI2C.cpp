#include <unordered_set>
#include <unordered_map>

#include<string>
#include <mutex>
#include <fcntl.h> // for O_RDWR
#include <sys/ioctl.h> // for ioctl
#include <unistd.h> // for write

#include "communication/SafeI2C.hpp"

bool SafeI2C::modified = true;

SafeI2C::SafeI2C(const std::string& dev, const int slave_addr) : dev_(dev), slave_addr_(slave_addr){
  {
    std::lock_guard<std::recursive_mutex> lock(m_);
    if(const auto it = in_use_.find(dev); it == in_use_.end()) {
      in_use_.insert(std::make_pair(dev, slave_addr));
      slave_captured_ = true;
    } else if (it->second.find(slave_addr) == it->second.end()) {
      it->second.insert(slave_addr);
      slave_captured_  = true;
    }
  }
  openDevice();
}

void SafeI2C::setDevice(const std::string& dev) {
  if(dev_ != dev) {
    std::lock_guard<std::recursive_mutex> lock(m_);
    if(const auto it = in_use_.find(dev); it == in_use_.end()) {
      in_use_.insert(std::make_pair(dev, std::unordered_set<int>()));
    }
    dev_ = dev;
    dev_modified = true;
  }
}

bool SafeI2C::openDevice() {
  std::lock_guard<std::recursive_mutex> lock(m_);
  // In case device has been updated
  if(dev_modified) {
    close(fd_);
    if(slave_captured_) {
      in_use_.find(dev_)->second.erase(slave_addr_);
      // NOTE: dont do this as others might have opened device but not captured slaves
      // if(it->second.empty()) {
      //   in_use_.erase(dev);
      // }
    }
    fd_ = open(dev_.c_str(), O_RDWR | O_NOCTTY | O_SYNC);
    dev_modified = false;
  } else if(fd_ < 0) {
    fd_ = open(dev_.c_str(), O_RDWR | O_NOCTTY | O_SYNC);
  }
  return (fd_ >=0);
}

void SafeI2C::setSlaveAddr(const int slave_addr) {
  std::lock_guard<std::recursive_mutex> lock(m_);
  if (auto it = in_use_.find(dev_); it->second.find(slave_addr) == it->second.end()) {
    it->second.insert(slave_addr);
    slave_captured_  = true;
  } else {
    slave_captured_ = false;
  }
  slave_addr_ = slave_addr;
}

bool SafeI2C::isDeviceOpen() {
  return (fd_ >= 0);
}

bool SafeI2C::isSlaveCaptured() {
  return slave_captured_;
}

// TODO: Use a map of bus to file descriptrs to prevent continuous open and close
bool SafeI2C::readI2c(const std::string& dev, const int slave_addr, char* buffer, const std::size_t length) {
  std::lock_guard<std::recursive_mutex> lock(m_);
  if(const auto found = in_use_.find(dev); found == in_use_.end() || found->second.find(slave_addr) != found->second.end()) {
    // this device is not in use  OR this device is in use and the slave_addr is not currently locked
    if(found != in_use_.end()) {
      modified = true;
    }

    if(const auto fd = open(dev.c_str(), O_RDWR | O_NOCTTY | O_SYNC); fd){
      if(ioctl(fd, I2C_SLAVE, slave_addr) >= 0) {
        const bool has_read = (read(fd, buffer, length) == length);
        close(fd);
        return has_read;
      } else {
        close(fd);
      }
    }
  }
  return false;
}

bool SafeI2C::writeI2c(const std::string& dev, const int slave_addr, char* buffer, const std::size_t length) {
  std::lock_guard<std::recursive_mutex> lock(m_);
  if(const auto found = in_use_.find(dev);
     found == in_use_.end() || found->second.find(slave_addr) != found->second.end()) {
    // this device is not in use  OR this device is in use and the slave_addr is not currently locked
    if(found != in_use_.end()) {
      modified = true;
    }

    if(const auto fd = open(dev.c_str(), O_RDWR | O_NOCTTY | O_SYNC); fd){
      if(ioctl(fd, I2C_SLAVE, slave_addr) >= 0) {
        const bool read = (write(fd, buffer, length) == length);
        close(fd);
        return read;
      } else {
        close(fd);
      }
    }
  }
  return false;
}

bool SafeI2C::checkI2c() {
  return isSlaveCaptured();
}

bool SafeI2C::readI2c(char* buffer, const std::size_t length) {
  if (modified && ioctl(fd_, I2C_SLAVE, slave_addr_) < 0) {
    return false;
  }
  if(read(fd_, buffer, length) ==  length) {
    return true;
  } else {
    return false;
  }
}

bool SafeI2C::writeI2c(char* buffer, const std::size_t length) {
  if (modified && ioctl(fd_, I2C_SLAVE, slave_addr_) < 0) {
    return false;
  }
  if(write(fd_, buffer, length) == length) {
    return true;
  } else {
    return false;
  }
}
