//
// Created by oleg on 8/6/18.
//

#include "LogFilter.hpp"

using namespace EagleEye::filters;

log_filter_t EagleEye::filters::by_level(LogLevel level)
{
    return [level](const LogEntry& entry) -> bool
    {
        return entry.level >= level;
    };
}
