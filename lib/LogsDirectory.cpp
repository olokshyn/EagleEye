//
// Created by oleg on 8/8/18.
//

#include "LogsDirectory.hpp"

#include <fstream>
#include <list>
#include <numeric>

#include "LogsParser.hpp"

#include "Utils.hpp"

using namespace EagleEye;

LogsDirectory::LogsDirectory(const std::string& log_dirname,
                             const IFormatParser& format_parser)
        : LogsDirectory(utils::files_in_dir(log_dirname), format_parser)
{

}

LogsDirectory::LogsDirectory(const std::vector<std::string>& log_filenames,
                             const IFormatParser& format_parser)
{
    for (const auto& filename : log_filenames)
    {
        std::ifstream stream(filename);
        if (!stream)
        {
            throw std::runtime_error(utils::concat_strs("Failed to open file: ", filename));
        }
        m_managers.emplace(
                std::make_pair(
                        utils::file_basename(filename),
                        LogsManager(parser::parse_logs(stream, format_parser))));
    }
}

const LogsManager& LogsDirectory::logs_manager(const std::string& filename) const
{
    auto iter = m_managers.find(utils::file_basename(filename));
    if (iter == m_managers.end())
    {
        throw std::runtime_error(utils::concat_strs("No manager for file: ", filename));
    }
    return iter->second;
}

LogsManager LogsDirectory::collect_results(
        const std::function<LogsManager(const LogsManager&)>& command) const
{
    std::list<std::vector<LogEntry>> results;
    for (const auto& [filename, manager] : m_managers)
    {
        results.push_back(command(manager).move_entries());
    }
    auto total_size = std::accumulate(results.begin(),
                                      results.end(),
                                      std::vector<LogsManager>::size_type(),
                                      [](auto size, const auto& entries)
                                      { return size + entries.size(); });
    std::vector<LogEntry> collected_entries;
    collected_entries.reserve(total_size);
    for (auto& result : results)
    {
        for (auto& entry : result)
        {
            collected_entries.push_back(std::move(entry));
        }
    }
    return LogsManager(std::move(collected_entries));
}
