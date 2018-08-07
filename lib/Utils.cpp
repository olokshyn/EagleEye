//
// Created by oleg on 8/7/18.
//

#include "Utils.hpp"

#include <ctime>

#include <iomanip>

using namespace EagleEye;

utils::date_time_t utils::date_time_t::empty()
{
    return date_time_t();
}

utils::date_time_t utils::date_time_t::from(std::istream& stream)
{
    std::tm tm = {};
    if (!(stream >> std::get_time(&tm, s_format)))
    {
        throw std::runtime_error("Failed to parse date-time");
    }
    return date_time_t(std::chrono::system_clock::from_time_t(std::mktime(&tm)));
}

utils::date_time_t utils::date_time_t::from(const std::string& str)
{
    std::stringstream stream(str);
    return from(stream);
}

void utils::date_time_t::set_format(const char* format)
{
    s_format = format;
}

std::string utils::date_time_t::to_string() const
{
    const size_t buffer_size = 64;

    std::time_t t1 = std::chrono::system_clock::to_time_t(*this);
    char buf[buffer_size];
    std::tm t2 = *std::localtime(&t1);
    buf[std::strftime(buf, buffer_size, "%Y-%m-%d %H-%M-%S", &t2)] = '\0';
    return std::string(buf);
}

const char* utils::date_time_t::s_format = "%Y-%m-%d %H:%M:%S";

utils::date_time_t::date_time_t(const std::chrono::system_clock::time_point& date_time)
    : std::chrono::system_clock::time_point(date_time)
{

}

std::ostream& utils::operator<<(std::ostream& stream, const date_time_t& date_time)
{
    return stream << date_time.to_string();
}

bool utils::operator==(const date_time_t& date_time, const std::string& str)
{
    return date_time == date_time_t::from(str);
}

bool utils::operator==(const std::string& str, const date_time_t& date_time)
{
    return operator==(date_time, str);
}
