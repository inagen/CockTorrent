#pragma once

#include <string>
#include <stdio.h>
#include <chrono>
#include <ctime>
#include <iomanip>

namespace util
{

auto CurrentDate() {
    auto time = std::chrono::system_clock::now();
    auto tm = std::chrono::system_clock::to_time_t(time);
    return std::put_time(std::localtime(&tm), "%Y-%m-%d %H:%M:%S");
}

}
