//
// Created by oleg on 8/6/18.
//

#ifndef EAGLEEYE_UTILS_HPP
#define EAGLEEYE_UTILS_HPP

#include <iosfwd>
#include <string>
#include <sstream>
#include <chrono>

namespace EagleEye::utils
{

template <typename T>
void _concat_strs(std::stringstream& stream, T arg)
{
    stream << arg;
}

template <typename T, typename... Args>
void _concat_strs(std::stringstream& stream, T arg, Args... args)
{
    stream << arg;
    _concat_strs(stream, args...);
}

template <typename... Args>
std::string concat_strs(Args... args)
{
    std::stringstream stream;
    _concat_strs(stream, args...);
    return stream.str();
}

typedef std::chrono::time_point<std::chrono::system_clock> date_time_t;
std::string date_time_to_string(const date_time_t& date_time);
date_time_t date_time_from_stream(std::stringstream& stream);
date_time_t date_time_from_string(const std::string& str);
std::ostream& operator<<(std::ostream& stream, const utils::date_time_t& date_time);

}

#endif //EAGLEEYE_UTILS_HPP
