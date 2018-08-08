//
// Created by oleg on 8/6/18.
//

#include "LogEntry.hpp"

#include <ctime>

#include <iostream>
#include <unordered_map>

#include "Utils.hpp"

using namespace EagleEye;

namespace
{

const std::unordered_map<std::string, LogEntryColumn> g_column_by_name = {
        {"log_level", LogEntryColumn::log_level},
        {"date_time", LogEntryColumn::date_time},
        {"message",   LogEntryColumn::message}
};

std::unordered_map<LogEntryColumn, std::string> inverse_column_map()
{
    std::unordered_map<LogEntryColumn, std::string> inversed;
    for (const auto& [key, value] : g_column_by_name)
    {
        inversed[value] = key;
    }
    return inversed;
};

}

LogEntryColumn LogEntry::get_column_by_name(const std::string& column_name)
{
    auto iter = g_column_by_name.find(column_name);
    if (iter == g_column_by_name.end())
    {
        throw std::runtime_error(
                utils::concat_strs("Failed to get column by name: unknown column ", column_name));
    }
    return iter->second;
}

std::string LogEntry::get_name_of_column(LogEntryColumn column)
{
    static const std::unordered_map<LogEntryColumn, std::string>
            s_name_by_column(inverse_column_map());

    auto iter = s_name_by_column.find(column);
    if (iter == s_name_by_column.end())
    {
        throw std::runtime_error(
                utils::concat_strs("Failed to get column name: ", static_cast<int>(column)));
    }
    return iter->second;
}

std::ostream& EagleEye::operator<<(std::ostream& stream, const LogEntry& entry)
{
    using date_time::operator<<;
    return stream << entry.date_time << " " << entry.level << " " << entry.message;
}
