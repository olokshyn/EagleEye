//
// Created by oleg on 8/7/18.
//

#include "LogsParser.hpp"

#include <iostream>

using namespace EagleEye;

std::vector<LogEntry> parser::parse_logs(
        std::istream& in, const EagleEye::IFormatParser& format_parser,
        size_t log_entries_hint)
{
    std::vector<LogEntry> entries;
    entries.reserve(log_entries_hint);

    std::string line;
    while (std::getline(in, line))
    {
        try
        {
            entries.push_back(format_parser.parse_line(line));
        }
        catch (const std::exception& exc)
        {
            std::cerr << "Failed to parse line: " << line << " " << exc.what() << std::endl;
        }
    }
    return entries;
}
