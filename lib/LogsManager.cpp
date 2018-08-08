//
// Created by oleg on 8/6/18.
//

#include "LogsManager.hpp"

#include <iterator>
#include <algorithm>
#include <iostream>

using namespace EagleEye;

LogsManager::LogsManager(std::vector<EagleEye::LogEntry>&& entries)
        : m_entries(std::move(entries))
{

}

const std::vector<LogEntry>& LogsManager::entries() const
{
    return m_entries;
}

std::vector<LogEntry>&& LogsManager::move_entries()
{
    return std::move(m_entries);
}

void LogsManager::filter(const filters::log_filter_t& filter)
{
    m_entries.erase(std::remove_if(m_entries.begin(), m_entries.end(), filter),
                    m_entries.end());
}

LogsManager LogsManager::filtered(const filters::log_filter_t& filter) const
{
    std::vector<LogEntry> filtered_entries;
    std::copy_if(m_entries.begin(), m_entries.end(),
                 std::back_inserter(filtered_entries), filter);
    return LogsManager(std::move(filtered_entries));
}


void LogsManager::sort(const sorters::log_sorter_t& sorter)
{
    std::sort(m_entries.begin(), m_entries.end(), sorter);
}

LogsManager LogsManager::sorted(const sorters::log_sorter_t& sorter) const
{
    std::vector<LogEntry> temp(m_entries);
    LogsManager manager(std::move(temp));
    manager.sort(sorter);
    return manager;
}

std::ostream& EagleEye::operator<<(std::ostream& stream, const LogsManager& manager)
{
    for (const auto& entry : manager.entries())
    {
        stream << entry << std::endl;
    }
    return stream;
}
