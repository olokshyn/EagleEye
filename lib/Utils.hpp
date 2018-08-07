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

// Creation of date_time_t objects on heap is prohibited.
class date_time_t : public std::chrono::system_clock::time_point
{
public:
    static date_time_t empty();
    static date_time_t from(std::istream& stream);
    static date_time_t from(const std::string& str);

    static void set_format(const char* format);

public:
    std::string to_string() const;

private:
    static const char* s_format;

private:
    date_time_t() = default;
    explicit date_time_t(const std::chrono::system_clock::time_point& date_time);
};

std::ostream& operator<<(std::ostream& stream, const date_time_t& date_time);
bool operator==(const date_time_t& date_time, const std::string& str);
bool operator==(const std::string& str, const date_time_t& date_time);

}

#endif //EAGLEEYE_UTILS_HPP
