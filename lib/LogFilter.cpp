//
// Created by oleg on 8/6/18.
//

#include "LogFilter.hpp"

#include <regex>

using namespace EagleEye::filters;

log_filter_t EagleEye::filters::by_level(LogLevel level)
{
    return [level](const LogEntry& entry) -> bool
    {
        return entry.level >= level;
    };
}

log_filter_t EagleEye::filters::by_level_exact(LogLevel level)
{
    return [level](const LogEntry& entry) -> bool
    {
        return entry.level == level;
    };
}

log_filter_t EagleEye::filters::by_date_time_ge(const utils::date_time_t& date_time)
{
    return [date_time](const LogEntry& entry) -> bool
    {
        return entry.date_time >= date_time;
    };
}

log_filter_t EagleEye::filters::by_date_time_le(const utils::date_time_t& date_time)
{
    return [date_time](const LogEntry& entry) -> bool
    {
        return entry.date_time <= date_time;
    };
}

log_filter_t EagleEye::filters::by_message(const std::string& rexp)
{
    std::regex regex(rexp);
    return [regex](const LogEntry& entry) -> bool
    {
        return std::regex_search(entry.message, regex);
    };
}
