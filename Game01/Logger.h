#pragma once
#include <iostream>
#include <chrono>
#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>

class Logger
{
public:
	Logger(const std::string& component);
	~Logger();
	void debug(const std::string& msg);
	void error(const std::string& msg);
	void info(const std::string& msg);
	void debug(const char* msg);
	void error(const char* msg);
	void info(const char* msg);
	void stop();

private:
	std::string component;
	std::string getCurrTime();
	const std::string LOG_FILE_NAME = "game02.log";
};

static std::ofstream* logFile;

