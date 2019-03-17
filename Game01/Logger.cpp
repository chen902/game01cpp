#include "Logger.h"

Logger::Logger(const std::string & component)
{
	this->component = component;
	if (!logFile) {
		logFile = new std::ofstream(LOG_FILE_NAME, std::ofstream::out | std::ofstream::app);
		info("Logger started");
	}
}

Logger::~Logger()
{
}

void Logger::debug(const std::string & msg)
{
	std::string time = getCurrTime();
	*logFile << time << " :: " << component << " :: DEBUG ::" << msg << std::endl;
	logFile->flush();
}

void Logger::error(const std::string & msg)
{
	std::string time = getCurrTime();
	*logFile << time << " :: " << component << " :: ERROR ::" << msg << std::endl;
	logFile->flush();
}

void Logger::info(const std::string & msg)
{
	std::string time = getCurrTime();
	*logFile << time << " :: " << component << " :: INFO ::" << msg << std::endl;
	logFile->flush();
}

void Logger::debug(const char * msg)
{
	debug(std::string(msg));
}

void Logger::error(const char * msg)
{
	error(std::string(msg));
}

void Logger::info(const char * msg)
{
	info(std::string(msg));
}

void Logger::stop()
{
	if (logFile) {
		info("Logger out.");
		logFile->close();
		delete logFile;
	}
}

/*
	Returns the current time
*/
std::string Logger::getCurrTime()
{
	std::stringstream ss;
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	std::time_t now_c = std::chrono::system_clock::to_time_t(now);
	ss << std::put_time(std::localtime(&now_c), "%F %T");
	return ss.str();
}
