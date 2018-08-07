//
// Created by oleg on 8/7/18.
//

#include "LogsParser.hpp"

#include <iostream>

using namespace EagleEye;

std::vector<LogEntry> parser::parse_logs(
        std::istream& in, const EagleEye::IFormatParser& format_parser,
        const log_level_parser_t& log_level_parser, size_t log_entries_hint)
{
    std::vector<LogEntry> entries;
    entries.reserve(log_entries_hint);

    std::string line;
    while (std::getline(in, line))
    {
        entries.push_back(format_parser.parse_line(line, log_level_parser));
    }
    return entries;
}
