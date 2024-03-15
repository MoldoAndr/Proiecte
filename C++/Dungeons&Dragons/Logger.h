#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>

unsigned long int get_log_count();

class Logger
{
public:
	static Logger& get_instance();
	static void	destroy_instance();
	void log_data(const char*, std::string);
private:
	inline static unsigned long int log_count{get_log_count()};
	inline static Logger* instance{ nullptr };
	Logger() = default;
	Logger(const Logger&) = delete;
	Logger(Logger&&) = delete;
};

#endif