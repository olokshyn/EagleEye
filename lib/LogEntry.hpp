//
// Created by oleg on 8/6/18.
//

#ifndef EAGLEEYE_LOGENTRY_HPP
#define EAGLEEYE_LOGENTRY_HPP

#include <iosfwd>
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

std::ostream& operator<<(std::ostream& stream, const LogEntry& entry);

}

#endif //EAGLEEYE_LOGENTRY_HPP
