//
// Created by oleg on 8/6/18.
//

#ifndef EAGLEEYE_LOGFILTER_HPP
#define EAGLEEYE_LOGFILTER_HPP

#include <sstream>
#include <functional>

#include "LogEntry.hpp"
#include "LogLevel.hpp"
#include "IFormatParser.hpp"

namespace EagleEye::filters
{

typedef std::function<bool(const LogEntry&)> log_filter_t;

enum class Relation
{
    less,
    less_eq,
    equal,
    greater_eq,
    greater
};

Relation parse_relation(std::istream& stream);

log_filter_t build_filter(LogEntryColumn column,
                          Relation relation,
                          const std::string& data,
                          const IFormatParser& format_parser);

log_filter_t build_message_filter(const std::string& rexp);

}

#endif //EAGLEEYE_LOGFILTER_HPP
