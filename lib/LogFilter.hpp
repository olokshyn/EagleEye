//
// Created by oleg on 8/6/18.
//

#ifndef EAGLEEYE_LOGFILTER_HPP
#define EAGLEEYE_LOGFILTER_HPP

#include <functional>

#include "LogEntry.hpp"
#include "LogLevel.hpp"

namespace EagleEye::filters
{

typedef std::function<bool(const LogEntry&)> log_filter_t;

log_filter_t by_level(LogLevel level);

log_filter_t by_level_exact(LogLevel level);

log_filter_t by_date_time_ge(const utils::date_time_t& date_time);

log_filter_t by_date_time_le(const utils::date_time_t& date_time);

log_filter_t by_message(const std::string& rexp);

}

#endif //EAGLEEYE_LOGFILTER_HPP
