//
// Created by oleg on 8/6/18.
//

#ifndef EAGLEEYE_IFORMATPARSER_HPP
#define EAGLEEYE_IFORMATPARSER_HPP

#include <string>

#include "LogEntry.hpp"
#include "LogLevel.hpp"

namespace EagleEye
{

class IFormatParser
{
public:
    virtual ~IFormatParser() = default;

    virtual LogEntry parse_line(const std::string& line) const = 0;

protected:
    virtual log_level_parser_t get_log_level_parser() const;
};

}

#endif //EAGLEEYE_IFORMATPARSER_HPP
