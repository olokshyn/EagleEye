//
// Created by oleg on 8/6/18.
//

#include "LogsManager.hpp"

#include <iterator>
#include <algorithm>
#include <iostream>

using namespace EagleEye;

LogsManager::LogsManager(std::istream& in, const EagleEye::IFormatParser& format_parser,
                         size_t log_entries_hint)
{
    m_entries.reserve(log_entries_hint);

    std::string line;
    while (std::getline(in, line))
    {
        m_entries.push_back(format_parser.parse_line(line));
    }
}

LogsManager::LogsManager(std::vector<EagleEye::LogEntry>&& entries)
    : m_entries(std::move(entries))
{

}

const std::vector<LogEntry>& LogsManager::entries() const
{
    return m_entries;
}

void LogsManager::filter(const EagleEye::log_filter_t& filter)
{
    m_entries.erase(std::remove_if(m_entries.begin(), m_entries.end(), filter),
                    m_entries.end());
}

LogsManager LogsManager::filtered(const EagleEye::log_filter_t& filter) const
{
    std::vector<LogEntry> filtered_entries;
    std::copy_if(m_entries.begin(), m_entries.end(),
                 std::back_inserter(filtered_entries), filter);
    return LogsManager(std::move(filtered_entries));
}
