#pragma once

#include <ctime>
#include <iostream>
#include <sstream>
#include <array>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <memory>

#define __FILENAME__ (__builtin_strrchr(__FILE__, '/') ? __builtin_strrchr(__FILE__, '/') + 1 : __FILE__)

#define LogDebug() LogDebugDetailed(__FILENAME__, __LINE__)
#define LogInfo() LogInfoDetailed(__FILENAME__, __LINE__)
#define LogStatus() LogStatusDetailed(__FILENAME__, __LINE__)
#define LogWarn() LogWarnDetailed(__FILENAME__, __LINE__)
#define LogErr() LogErrorDetailed(__FILENAME__, __LINE__)

enum class Colour { BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE, RESET };

void set_display_colour(Colour colour);

class LogDetailed{
public:
	LogDetailed(const char *filename, int filenumber):_s(), _caller_filename(filename), _caller_filenumber(filenumber) {}

	template <typename T> LogDetailed &operator<<(const T &x){
		_s << x;
		std::string _str = _s.str();
		return *this;
	}

	virtual ~LogDetailed(){
		switch (_log_level){
		case LogLevel::Debug:
			set_display_colour(Colour::GREEN);
			break;
		case LogLevel::Info:
			set_display_colour(Colour::BLUE);
			break;
		case LogLevel::Warn:
			set_display_colour(Colour::YELLOW);
			break;
		case LogLevel::Err:
			set_display_colour(Colour::RED);
			break;
		case LogLevel::Status:
			set_display_colour(Colour::WHITE);
			break;
		}

		if (_log_level == LogLevel::Status){
			std::cout << _s.str();
			set_display_colour(Colour::RESET);
			std::cout << std:: endl;
		}
		else{
			time_t rawtime;
			time(&rawtime);
			struct tm *timeinfo = localtime(&rawtime);
			char time_buffer[10]{};
			strftime(time_buffer, sizeof(time_buffer), "%I:%M:%S", timeinfo);
			std::cout << "[" << time_buffer;

			switch(_log_level){
			case LogLevel::Debug:
				std::cout << "|Debug ] ";
				break;
			case LogLevel::Info:
				std::cout << "|Info ] ";
				break;
			case LogLevel::Warn:
				std::cout << "|Warn ] ";
				break;
			case LogLevel::Err:
				std::cout << "|Error ] ";
				break;
			case LogLevel::Status:
				std::cout << "|Status ] ";
				break;
			}
			set_display_colour(Colour::RESET);
			std::cout << _s.str();
			std::cout << " |" << _caller_filename << ":" << _caller_filenumber << "|";
			std::cout << std::endl;
		}
	}

protected:
	enum  LogLevel {Debug, Info, Warn, Err, Status} _log_level;

private:
	std::stringstream _s;
	const char *_caller_filename;
	int _caller_filenumber;
};

class LogDebugDetailed : public LogDetailed{
public:
	LogDebugDetailed(const char *filename, int filenumber) : LogDetailed(filename, filenumber){
		_log_level = LogLevel::Debug;
	}
};

class LogInfoDetailed : public LogDetailed{
public:
	LogInfoDetailed(const char *filename, int filenumber) : LogDetailed(filename, filenumber){
		_log_level = LogLevel::Info;
	}
};

class LogWarnDetailed : public LogDetailed{
public:
	LogWarnDetailed(const char *filename, int filenumber) : LogDetailed(filename, filenumber){
		_log_level = LogLevel::Warn;
	}
};

class LogErrorDetailed : public LogDetailed{
public:
	LogErrorDetailed(const char *filename, int filenumber) : LogDetailed(filename, filenumber){
		_log_level = LogLevel::Err;
	}
};

class LogStatusDetailed : public LogDetailed{
public:
	LogStatusDetailed(const char *filename, int filenumber) : LogDetailed(filename, filenumber){
		_log_level = LogLevel::Status;
	}
};
