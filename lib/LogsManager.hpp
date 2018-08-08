//
// Created by oleg on 8/6/18.
//

#ifndef EAGLEEYE_LOGSMANAGER_HPP
#define EAGLEEYE_LOGSMANAGER_HPP

#include <iosfwd>

#include "LogEntry.hpp"
#include "IFormatParser.hpp"
#include "LogFilter.hpp"
#include "LogSorter.hpp"

namespace EagleEye
{

class LogsManager
{
public:
    explicit LogsManager(std::vector<LogEntry>&& entries);

    LogsManager(const LogsManager& other) = default;
    LogsManager(LogsManager&& other) = default;

    LogsManager& operator=(const LogsManager& other) = default;
    LogsManager& operator=(LogsManager&& other) = default;

    const std::vector<LogEntry>& entries() const;

    void filter(const filters::log_filter_t& filter);
    LogsManager filtered(const filters::log_filter_t& filter) const;

    void sort(const sorters::log_sorter_t& sorter);
    LogsManager sorted(const sorters::log_sorter_t& sorter) const;

private:
    std::vector<LogEntry> m_entries;
};

std::ostream& operator<<(std::ostream& stream, const LogsManager& manager);

}

#endif //EAGLEEYE_LOGSMANAGER_HPP
