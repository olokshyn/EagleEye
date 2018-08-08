//
// Created by oleg on 8/8/18.
//

#include "IFormatParser.hpp"

using namespace EagleEye;

LogLevel IFormatParser::parse_log_level(const std::string& str) const
{
    return log_level_parser(str);
}

date_time::date_time_t IFormatParser::parse_date_time(std::istream& stream) const
{
    return date_time::from(stream);
}

date_time::date_time_t IFormatParser::parse_date_time(const std::string& str) const
{
    return date_time::from(str);
}
