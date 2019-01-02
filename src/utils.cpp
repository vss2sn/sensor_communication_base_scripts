/*
Useful functions
*/

#include "utils.h"

// For Debugging
#define ANSI_COLOUR_BLACK "\x1b[1;30m"
#define ANSI_COLOUR_RED "\x1b[1;31m"
#define ANSI_COLOUR_GREEN "\x1b[1;32m"
#define ANSI_COLOUR_YELLOW "\x1b[1;33m"
#define ANSI_COLOUR_BLUE "\x1b[1;34m"
#define ANSI_COLOUR_MAGENTA "\x1b[1;35m"
#define ANSI_COLOUR_CYAN "\x1b[1;36m"
#define ANSI_COLOUR_WHITE "\x1b[1;37m"
#define ANSI_COLOUR_RESET "\x1b[1;0m"

void set_display_colour(Colour colour){
	switch (colour){
	case Colour::BLACK:
		std::cout << ANSI_COLOUR_BLACK;
		break;
	case Colour::RED:
		std::cout << ANSI_COLOUR_RED;
		break;
	case Colour::GREEN:
		std::cout << ANSI_COLOUR_GREEN;
		break;
	case Colour::YELLOW:
		std::cout << ANSI_COLOUR_YELLOW;
		break;
	case Colour::BLUE:
		std::cout << ANSI_COLOUR_BLUE;
		break;
	case Colour::MAGENTA:
		std::cout << ANSI_COLOUR_MAGENTA;
		break;
	case Colour::CYAN:
		std::cout << ANSI_COLOUR_CYAN;
		break;
	case Colour::WHITE:
		std::cout << ANSI_COLOUR_WHITE;
		break;
	case Colour::RESET:
		std::cout << ANSI_COLOUR_RESET;
		break;
	}
}

std::string exec_system_cmd(const char* cmd){
	std::array<char, 128> buffer;
	std::string result;
	std::unique_ptr<FILE, decltype(&pclose) > pipe(popen(cmd, "r"), pclose);
	if(!pipe){
		std::cout << "Unable to run system call" + std::string(cmd);
		return "";
	}
	else{
		while(fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
			result += buffer.data();
		return result;
	}
}


#ifdef BUILD_INDIVIDUAL
int main(){
	//Example use:
	/*
	LogDebug() << "Green";
	LogInfo()  << "Blue";
	LogWarn()  << "Yellow";
	LogErr()   << "Red";
	LogStatus()<<	"White";
	*/
}
#endif
