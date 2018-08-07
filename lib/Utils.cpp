//
// Created by oleg on 8/7/18.
//

#include "Utils.hpp"

#include <ctime>

#include <iomanip>

using namespace EagleEye;

std::string utils::date_time_to_string(const date_time_t& date_time)
{
    const size_t buffer_size = 64;

    std::time_t t1 = std::chrono::system_clock::to_time_t(date_time);
    char buf[buffer_size];
    std::tm t2 = *std::localtime(&t1);
    buf[std::strftime(buf, buffer_size, "%Y-%m-%d %H-%M-%S", &t2)] = '\0';
    return std::string(buf);
}

utils::date_time_t utils::date_time_from_stream(std::stringstream& stream)
{
    std::tm tm = {};
    if (!(stream >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S")))
    {
        throw std::runtime_error(utils::concat_strs("Failed to parse date-time: ", stream.str()));
    }
    return std::chrono::system_clock::from_time_t(std::mktime(&tm));
}

utils::date_time_t utils::date_time_from_string(const std::string& str)
{
    std::stringstream stream(str);
    return date_time_from_stream(stream);
}

std::ostream& utils::operator<<(std::ostream& stream, const date_time_t& date_time)
{
    return stream << date_time_to_string(date_time);
}
