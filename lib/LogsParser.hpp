//
// Created by oleg on 8/7/18.
//

#ifndef EAGLEEYE_LOGSPARSER_HPP
#define EAGLEEYE_LOGSPARSER_HPP

#include <iosfwd>
#include <vector>

#include "IFormatParser.hpp"
#include "LogEntry.hpp"
#include "LogLevel.hpp"

namespace EagleEye::parser
{

std::vector<LogEntry> parse_logs(std::istream& in,
                                 const IFormatParser& format_parser,
                                 size_t log_entries_hint = 0);

std::vector<LogEntry> parse_logs(const std::string& filename,
                                 const IFormatParser& format_parser);

std::vector<LogEntry> parse_logs(const std::vector<std::string>& filenames,
                                 const IFormatParser& format_parser);

std::vector<LogEntry> parse_logs_dir(const std::string& dirname,
                                     const IFormatParser& format_parser);

}


#endif //EAGLEEYE_LOGSPARSER_HPP
