//
// Created by oleg on 8/6/18.
//

#include "PythonFormatParser.hpp"

#include <sstream>

#include "Utils.hpp"

using namespace EagleEye;

LogEntry PythonFormatParser::parse_line(const std::string& line) const
{
    LogEntry entry;

    std::stringstream stream(line);
    entry.date_time = parse_date_time(stream);
    stream.ignore(4); // skip milliseconds

    std::string log_level;
    if (!(stream >> std::ws >> log_level))
    {
        throw std::runtime_error(utils::concat_strs("Failed to parse log level: ", line));
    }
    entry.level = parse_log_level(log_level);

    // ignore errors: the log may have empty message
    std::getline(stream >> std::ws, entry.message);

    return entry;
}
