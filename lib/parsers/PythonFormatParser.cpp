//
// Created by oleg on 8/6/18.
//

#include "PythonFormatParser.hpp"

#include <sstream>

#include "Utils.hpp"

using namespace EagleEye;

LogEntry PythonFormatParser::parse_line(const std::string& line,
                                        const log_level_parser_t& log_level_parser) const
{
    LogEntry entry;

    std::stringstream stream(line);
    entry.date_time = utils::date_time_t::from(stream);
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
