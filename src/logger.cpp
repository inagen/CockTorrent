#include "logger.h"
#include "utilities.h"
#include <fstream>
#include <string>

const char *test() {
    return "HELLO";
}

#include "logger.h"
#include "utilities.h"
#include <fstream>
#include <string>

Logger* Logger::get_instance() {
    static Logger logger;
    return &logger;
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