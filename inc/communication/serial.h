class SERIAL{
protected:
  int fd;
  std::string dev;
  unsigned char readbuf[];
public:
  SERIAL();
  ~SERIAL();
  int set_interface_attribs(int fd, int speed, int parity);
  void set_blocking(int fd, int should_block);
  int read_with_timout();
  std::string read_string_with_timout();
  int write_string_to_serial(std::string tag);
  bool open_device();
};
