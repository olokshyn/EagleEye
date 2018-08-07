//
// Created by oleg on 8/7/18.
//

#ifndef EAGLEEYE_DATETIME_HPP
#define EAGLEEYE_DATETIME_HPP

#include <iosfwd>
#include <string>
#include <chrono>

namespace EagleEye::date_time
{

typedef std::chrono::system_clock::time_point date_time_t;

extern const char* g_format;

date_time_t from(std::istream& stream);

date_time_t from(const std::string& str);

std::string to_string(const date_time_t& date_time);

std::ostream& operator<<(std::ostream& stream, const date_time_t& date_time);

bool operator==(const date_time_t& date_time, const std::string& str);

bool operator==(const std::string& str, const date_time_t& date_time);

}

#endif //EAGLEEYE_DATETIME_HPP
