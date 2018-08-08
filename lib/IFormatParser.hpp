//
// Created by oleg on 8/6/18.
//

#ifndef EAGLEEYE_IFORMATPARSER_HPP
#define EAGLEEYE_IFORMATPARSER_HPP

#include <string>

#include "LogEntry.hpp"
#include "LogLevel.hpp"
#include "DateTime.hpp"

namespace EagleEye
{

class IFormatParser
{
public:
    virtual ~IFormatParser() = default;

    virtual LogEntry parse_line(const std::string& line) const = 0;

    virtual LogLevel parse_log_level(const std::string& str) const;
    virtual date_time::date_time_t parse_date_time(std::istream& stream) const;
    virtual date_time::date_time_t parse_date_time(const std::string& str) const;
};

}

#endif //EAGLEEYE_IFORMATPARSER_HPP
