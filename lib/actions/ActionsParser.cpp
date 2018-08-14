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

std::unique_ptr<IAction> parse_filter_action(const std::vector<std::string>& tokens,
                                             const IFormatParser& format_parser)
{
    if (tokens.size() != 4)
    {
        throw std::runtime_error("Invalid tokens: 4 tokens is needed for filter action");
    }

    LogEntryColumn column = LogEntry::get_column_by_name(tokens[1]);
    filters::Relation relation = filters::get_relation(tokens[2]);

    return std::make_unique<FilteringAction>(
            filters::build_filter(column, relation, tokens[3], format_parser));
}

std::unique_ptr<IAction> parse_sort_action(const std::vector<std::string>& tokens,
                                           const IFormatParser& format_parser)
{
    if (tokens.size() != 3)
    {
        throw std::runtime_error("Invalid tokens: 3 tokens is needed for sorting action");
    }

    LogEntryColumn column = LogEntry::get_column_by_name(tokens[1]);
    bool ascending;
    if (tokens[2] == "asc")
    {
        ascending = true;
    }
    else if (tokens[2] == "desc")
    {
        ascending = false;
    }
    else
    {
        throw std::runtime_error(utils::concat_strs("Failed to parse sorting order: ", tokens[2]));
    }

    return std::make_unique<SortingAciton>(sorters::build_log_sorter(column, ascending));
}

}

std::unique_ptr<IAction> actions::parse_action(const std::vector<std::string>& tokens,
                                               const IFormatParser& format_parser)
{
    if (tokens.empty())
    {
        throw std::runtime_error("Invalid tokens");
    }
    if (tokens[0] == "filter")
    {
        return parse_filter_action(tokens, format_parser);
    }
    else if (tokens[0] == "sort")
    {
        return parse_sort_action(tokens, format_parser);
    }
    else
    {
        throw std::runtime_error(
                utils::concat_strs("Failed to parse action, unknown type: ", tokens[0]));
    }
}
