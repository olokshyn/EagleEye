//
// Created by oleg on 8/7/18.
//

#include "DateTime.hpp"

#include <ctime>

#include <iomanip>

using namespace EagleEye;
using namespace EagleEye::date_time;

const char* date_time::g_format = "%Y-%m-%d %H:%M:%S";

date_time_t date_time::from(std::istream& stream)
{
    std::tm tm = {};
    if (!(stream >> std::get_time(&tm, g_format)))
    {
        throw std::runtime_error("Failed to parse date-time");
    }
    return date_time_t(std::chrono::system_clock::from_time_t(std::mktime(&tm)));
}

date_time_t date_time::from(const std::string& str)
{
    std::stringstream stream(str);
    return from(stream);
}

std::string date_time::to_string(const date_time_t& date_time)
{
    const size_t buffer_size = 64;

    std::time_t t1 = std::chrono::system_clock::to_time_t(date_time);
    char buf[buffer_size];
    std::tm t2 = *std::localtime(&t1);
    buf[std::strftime(buf, buffer_size, "%Y-%m-%d %H-%M-%S", &t2)] = '\0';
    return std::string(buf);
}

std::ostream& date_time::operator<<(std::ostream& stream, const date_time_t& date_time)
{
    return stream << to_string(date_time);
}

bool date_time::operator==(const date_time_t& date_time, const std::string& str)
{
    return date_time == from(str);
}

bool date_time::operator==(const std::string& str, const date_time_t& date_time)
{
    return operator==(date_time, str);
}
