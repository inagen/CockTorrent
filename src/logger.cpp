#include "logger.h"
#include "utilities.h"
#include <fstream>
#include <string>

Logger* Logger::logger_instance = nullptr;
std::ofstream Logger::file;

Logger* Logger::GetInstance() {
	if (logger_instance == nullptr) {
		logger_instance = new Logger;
		file.open(LOG_FILE_PATH, std::ios::out | std::ios::app);
	}
	return logger_instance;
}

void Logger::Write(const std::string &msg_type, const std::string & msg) {
	file << msg_type << "\t" << util::CurrentDate() << "\t" << " " << msg << "\n";
}

void Logger::Debug(const std::string &msg) {
	Write("[DEBUG]", msg);
}

void Logger::Info(const std::string &msg) {
	Write("[INFO]", msg);
}

void Logger::Warning(const std::string &msg) {
	Write("[WARNING]", msg);
}

void Logger::Error(const std::string &msg) {
	Write("[ERROR]", msg);
}
