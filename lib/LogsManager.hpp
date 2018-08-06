//
// Created by oleg on 8/6/18.
//

#ifndef EAGLEEYE_LOGSMANAGER_HPP
#define EAGLEEYE_LOGSMANAGER_HPP

#include <iosfwd>

#include "LogEntry.hpp"
#include "IFormatParser.hpp"
#include "LogFilter.hpp"

namespace EagleEye
{

class LogsManager
{
public:
    LogsManager(std::istream& in,
                const IFormatParser& format_parser,
                const log_level_parser_t& log_level_parser = default_log_level_parser,
                size_t log_entries_hint = 0);
    explicit LogsManager(std::vector<LogEntry>&& entries);

    LogsManager(const LogsManager& other) = default;
    LogsManager(LogsManager&& other) = default;

    const std::vector<LogEntry>& entries() const;

    void filter(const log_filter_t& filter);
    LogsManager filtered(const log_filter_t& filter) const;

private:
    std::vector<LogEntry> m_entries;
};

std::ostream& operator<<(std::ostream& stream, const LogsManager& manager);

}

#endif //EAGLEEYE_LOGSMANAGER_HPP
