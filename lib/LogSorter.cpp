//
// Created by oleg on 8/6/18.
//

#include "LogSorter.hpp"

using namespace EagleEye;
using namespace EagleEye::sorters;

log_sorter_t sorters::build_log_sorter(LogEntryColumn column, bool ascending)
{
    switch (column)
    {
    case LogEntryColumn::log_level:
        return [ascending](const LogEntry& left, const LogEntry& right) -> bool
        {
            return ascending ? left.level < right.level : left.level > right.level;
        };

    case LogEntryColumn::date_time:
        return [ascending](const LogEntry& left, const LogEntry& right) -> bool
        {
            return ascending ? left.date_time < right.date_time : left.date_time > right.date_time;
        };

    case LogEntryColumn::message:
        return [ascending](const LogEntry& left, const LogEntry& right) -> bool
        {
            return ascending ? left.message < right.message : left.message > right.message;
        };
    }

    throw std::runtime_error("Failed to build sorter");
}
