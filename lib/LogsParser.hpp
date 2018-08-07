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
                                 const log_level_parser_t& log_level_parser = default_log_level_parser,
                                 size_t log_entries_hint = 0);

}


#endif //EAGLEEYE_LOGSPARSER_HPP
