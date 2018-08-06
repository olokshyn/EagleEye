//
// Created by oleg on 8/6/18.
//

#ifndef EAGLEEYE_LOGENTRY_HPP
#define EAGLEEYE_LOGENTRY_HPP

#include <string>
#include <chrono>

#include "LogLevel.hpp"

namespace EagleEye
{

struct LogEntry
{
    LogLevel level;
    std::chrono::time_point<std::chrono::system_clock> date;
    std::string message;
};

}

#endif //EAGLEEYE_LOGENTRY_HPP
