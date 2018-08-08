//
// Created by oleg on 8/6/18.
//

#include "LogFilter.hpp"

#include <regex>
#include <unordered_map>

#include "Utils.hpp"

using namespace EagleEye;
using namespace EagleEye::filters;

Relation filters::parse_relation(std::istream& stream)
{
    static const std::unordered_map<std::string, Relation> s_map = {
            {"<", Relation::less},
            {"<=", Relation::less_eq},
            {"==", Relation::equal},
            {">=", Relation::greater_eq},
            {">", Relation::greater}
    };

    std::string relation;
    stream >> relation;
    auto iter = s_map.find(relation);
    if (iter == s_map.end())
    {
        throw std::runtime_error(
                utils::concat_strs("Failed to parse filter action: unknown operation: ", relation));
    }
    return iter->second;
}

log_filter_t filters::build_filter(LogEntryColumn column,
                                   Relation relation,
                                   const std::string& data,
                                   const IFormatParser& format_parser)
{
    switch (column)
    {
    case LogEntryColumn::log_level:
    {
        auto level = format_parser.parse_log_level(data);
        switch (relation)
        {
        case Relation::less:
            return [level](const LogEntry& entry) -> bool
            {
                return entry.level < level;
            };
        case Relation::less_eq:
            return [level](const LogEntry& entry) -> bool
            {
                return entry.level <= level;
            };
        case Relation::equal:
            return [level](const LogEntry& entry) -> bool
            {
                return entry.level == level;
            };
        case Relation::greater_eq:
            return [level](const LogEntry& entry) -> bool
            {
                return entry.level >= level;
            };
        case Relation::greater:
            return [level](const LogEntry& entry) -> bool
            {
                return entry.level > level;
            };
        }
        break;
    }

    case LogEntryColumn::date_time:
    {
        auto date_time = format_parser.parse_date_time(data);
        switch (relation)
        {
        case Relation::less:
            return [date_time](const LogEntry& entry) -> bool
            {
                return entry.date_time < date_time;
            };
        case Relation::less_eq:
            return [date_time](const LogEntry& entry) -> bool
            {
                return entry.date_time <= date_time;
            };
        case Relation::equal:
            return [date_time](const LogEntry& entry) -> bool
            {
                return entry.date_time == date_time;
            };
        case Relation::greater_eq:
            return [date_time](const LogEntry& entry) -> bool
            {
                return entry.date_time >= date_time;
            };
        case Relation::greater:
            return [date_time](const LogEntry& entry) -> bool
            {
                return entry.date_time > date_time;
            };
        }
        break;
    }

    case LogEntryColumn::message:
        return build_message_filter(data);
    }

    throw std::runtime_error("Failed to build filter");
}

log_filter_t filters::build_message_filter(const std::string& rexp)
{
    std::regex regex(rexp);
    return [regex](const LogEntry& entry) -> bool
    {
        return std::regex_search(entry.message, regex);
    };
}
