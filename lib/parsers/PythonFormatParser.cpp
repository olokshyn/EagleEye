//
// Created by oleg on 8/6/18.
//

#include "PythonFormatParser.hpp"

#include <ctime>
#include <iomanip>
#include <sstream>

#include "utils.hpp"

using namespace EagleEye;

LogEntry PythonFormatParser::parse_line(const std::string& line,
                                        const log_level_parser_t& log_level_parser) const
{
    LogEntry entry;

    std::stringstream stream(line);
    std::tm tm = {};
    if (!(stream >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S")))
    {
        throw std::runtime_error(utils::concat_strs("Failed to parse date-time: ", line));
    }
    entry.date = std::chrono::system_clock::from_time_t(std::mktime(&tm));
    stream.ignore(4); // skip milliseconds

    std::string log_level;
    if (!(stream >> std::ws >> log_level))
    {
        throw std::runtime_error(utils::concat_strs("Failed to parse log level: ", line));
    }
    entry.level = log_level_parser(log_level);

    if (!std::getline(stream >> std::ws, entry.message))
    {
        throw std::runtime_error(utils::concat_strs("Failed to parse message: ", line));
    }

    return entry;
}
