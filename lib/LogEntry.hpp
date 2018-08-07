//
// Created by oleg on 8/6/18.
//

#ifndef EAGLEEYE_LOGENTRY_HPP
#define EAGLEEYE_LOGENTRY_HPP

#include <iosfwd>
#include <string>
#include <chrono>

#include "LogLevel.hpp"
#include "DateTime.hpp"

namespace EagleEye
{

struct LogEntry
{
    LogLevel level;
    date_time::date_time_t date_time;
    std::string message;
};

std::ostream& operator<<(std::ostream& stream, const LogEntry& entry);

}

#endif //EAGLEEYE_LOGENTRY_HPP
