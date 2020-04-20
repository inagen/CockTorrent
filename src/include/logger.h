#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>

#define LOG_FILE_PATH "log.txt"

class Logger {
private:
    std::ofstream file{LOG_FILE_PATH};

public:
    static Logger *get_instance();

    void Debug(const std::string &);

    void Info(const std::string &);

    void Warning(const std::string &);

    void Error(const std::string &);

private:
    ~Logger() = default;

    Logger() = default;

    Logger(const Logger &);

    void Write(const std::string &, const std::string &);

    Logger &operator=(const Logger &) { return *this; };
};

#endif //LOGGER_H