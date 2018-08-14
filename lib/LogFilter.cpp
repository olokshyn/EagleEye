//
// Created by oleg on 8/6/18.
//

#include "LogFilter.hpp"

#include <regex>
#include <unordered_map>

#include "Utils.hpp"

using namespace EagleEye;
using namespace EagleEye::filters;

Relation filters::get_relation(const std::string& relation_name)
{
    static const std::unordered_map<std::string, Relation> s_map = {
            {"<", Relation::less},
            {"<=", Relation::less_eq},
            {"==", Relation::equal},
            {"!=", Relation::not_equal},
            {">=", Relation::greater_eq},
            {">", Relation::greater}
    };

    auto iter = s_map.find(relation_name);
    if (iter == s_map.end())
    {
        throw std::runtime_error(
                utils::concat_strs("Failed to parse filter action: unknown operation: ",
                                   relation_name));
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
        case Relation::not_equal:
            return [level](const LogEntry& entry) -> bool
            {
                return entry.level != level;
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
        case Relation::not_equal:
            return [date_time](const LogEntry& entry) -> bool
            {
                return entry.date_time != date_time;
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
        switch (relation)
        {
        case Relation::equal:
            return build_message_filter(data);
        case Relation::not_equal:
            return std::not_fn(build_message_filter(data));
        default:
            throw std::runtime_error("Only == and != are supported for message column");
        }
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
