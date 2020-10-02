
class Serial {
private:
  int fd;
  std::string dev;
  unsigned char readbuf[256];
public:
  int setInterfaceAttribs(int fd, int speed, int parity);
  void setBlocking(int fd, int should_block);
  int readWithTimout();
  std::string readStringWithTimout();
  int writeString(const std::string& tag);
  bool openDevice();
};
