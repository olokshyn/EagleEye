//
// Created by oleg on 8/8/18.
//

#include "ActionsParser.hpp"

#include <iostream>
#include <string>
#include <sstream>

#include "LogFilter.hpp"
#include "LogSorter.hpp"
#include "FilteringAction.hpp"
#include "SortingAciton.hpp"

#include "Utils.hpp"

using namespace EagleEye;
using namespace EagleEye::actions;

namespace
{

std::unique_ptr<IAction> parse_filter_action(std::istream& stream,
                                             const IFormatParser& format_parser)
{
    std::string column_name;
    stream >> column_name;
    LogEntryColumn column = LogEntry::get_column_by_name(column_name);
    filters::Relation relation = filters::parse_relation(stream);
    std::string data;
    stream >> data;

    return std::make_unique<FilteringAction>(
            filters::build_filter(column, relation, data, format_parser));
}

std::unique_ptr<IAction> parse_sort_action(std::istream& stream,
                                           const IFormatParser& format_parser)
{
    std::string column_name;
    stream >> column_name;
    LogEntryColumn column = LogEntry::get_column_by_name(column_name);
    std::string order;
    stream >> order;
    bool ascending;
    if (order == "asc")
    {
        ascending = true;
    }
    else if (order == "desc")
    {
        ascending = false;
    }
    else
    {
        throw std::runtime_error(utils::concat_strs("Failed to parse sorting order: ", order));
    }

    return std::make_unique<SortingAciton>(sorters::build_log_sorter(column, ascending));
}

}

std::list<std::unique_ptr<IAction>> actions::parse_actions(std::istream& stream,
                                                           const IFormatParser& format_parser)
{
    std::list<std::unique_ptr<IAction>> actions;
    std::string action;
    while (std::getline(stream, action, ','))
    {
        std::stringstream action_stream(action);
        action_stream.exceptions(std::istream::failbit | std::istream::badbit);
        std::string action_type;
        action_stream >> action_type;
        if (action_type == "filter")
        {
            actions.push_back(parse_filter_action(action_stream, format_parser));
        }
        else if (action_type == "sort")
        {
            actions.push_back(parse_sort_action(action_stream, format_parser));
        }
        else
        {
            throw std::runtime_error(
                    utils::concat_strs("Failed to parse action, unknown type: ", action));
        }
    }
    return actions;
}
