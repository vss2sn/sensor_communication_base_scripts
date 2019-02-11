#define gettid() syscall(SYS_gettid)
void invoke_thread(void(*f)(),std::string tag);
void my_func();
void sig_wait();
