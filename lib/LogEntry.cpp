//
// Created by oleg on 8/6/18.
//

#include "LogEntry.hpp"

#include <ctime>

#include <iostream>

std::ostream& EagleEye::operator<<(std::ostream& stream, const LogEntry& entry)
{
    const size_t buffer_size = 64;

    std::time_t t1 = std::chrono::system_clock::to_time_t(entry.date);
    char buf[buffer_size];
    std::tm t2 = *std::localtime(&t1);
    buf[std::strftime(buf, buffer_size, "%Y-%m-%d %H-%M-%S", &t2)] = '\0';
    stream << buf << " " << entry.level << " " << entry.message;

    return stream;
}
