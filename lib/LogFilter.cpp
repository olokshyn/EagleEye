//
// Created by oleg on 8/6/18.
//

#include "LogFilter.hpp"

using namespace EagleEye;

log_filter_t EagleEye::build_level_filter(LogLevel level)
{
    return [level](const LogEntry& entry) -> bool
    {
        return entry.level >= level;
    };
}
