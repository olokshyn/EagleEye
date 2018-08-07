//
// Created by oleg on 8/6/18.
//

#include "LogSorter.hpp"

EagleEye::sorters::log_sorter_t EagleEye::sorters::by_level(bool ascending)
{
    return [ascending](const LogEntry& left, const LogEntry& right) -> bool
    {
        return ascending ? left.level < right.level : left.level > right.level;
    };
}

EagleEye::sorters::log_sorter_t EagleEye::sorters::by_date_time(bool ascending)
{
    return [ascending](const LogEntry& left, const LogEntry& right) -> bool
    {
        return ascending ? left.date_time < right.date_time : left.date_time > right.date_time;
    };
}
