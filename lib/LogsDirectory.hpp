//
// Created by oleg on 8/8/18.
//

#ifndef EAGLEEYE_LOGSDIRECTORY_HPP
#define EAGLEEYE_LOGSDIRECTORY_HPP

#include <vector>
#include <string>
#include <functional>
#include <unordered_map>

#include "LogsManager.hpp"
#include "IFormatParser.hpp"

namespace EagleEye
{

class LogsDirectory
{
public:
    explicit LogsDirectory(const std::string& log_dirname,
                           const IFormatParser& format_parser);

    explicit LogsDirectory(const std::vector<std::string>& log_filenames,
                           const IFormatParser& format_parser);

    const LogsManager& logs_manager(const std::string& filename) const;

    LogsManager collect_results(
            const std::function<LogsManager(const LogsManager& manager)>& command) const;

private:
    std::unordered_map<std::string, LogsManager> m_managers;
};

}

#endif //EAGLEEYE_LOGSDIRECTORY_HPP
