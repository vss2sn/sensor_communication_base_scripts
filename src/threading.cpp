#include "threading.h"

bool run = true; //Using this variable to exit loops and close when keybpard interrupt called

void invoke_thread(void(*f)(), std::string tag)
{
	std::thread::id thread_id = std::this_thread::get_id();
	pid_t thread_tid = gettid();
	std::cout << "Thread ID: " << thread_id << std::endl;
	std::cout << "Thread TID: " << thread_tid << std::endl;
	std::cout << "Function name:" << tag << std::endl;
	(*f)();
}

void example_func(){
	int i = 0;
#ifdef BOOST_FOUND
	while(run){
#else
	while(true){
#endif
		usleep(1000000);
		std::cout<<i<<std::endl;
		i+=1;
	}
}


void sig_wait() {
#ifdef BOOST_FOUND
  boost::asio::io_service ios;
  boost::asio::signal_set signals(ios, SIGINT, SIGTERM);
  signals.async_wait([&](boost::system::error_code const &, int) {});
  ios.run();
#else
  std::cout << "Boost not found. sig_wait() does not work." <<  std::endl;
#endif
}


#ifdef BUILD_INDIVIDUAL
int main(){
	std::thread::id thread_id = std::this_thread::get_id();
	pid_t thread_tid = gettid();
	std::vector<std::thread*> threads;

	std::thread *thread= new std::thread(&invoke_thread, &example_func, tag);
	threads.push_back(thread);

	sig_wait();
	run=false;
	threads.back()->join();
	return 0;
}
#endif
