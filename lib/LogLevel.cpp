//
// Created by oleg on 8/6/18.
//


#include "LogLevel.hpp"

#include <cctype>

#include <unordered_map>
#include <algorithm>
#include <iomanip>

#include "Utils.hpp"

using namespace EagleEye;

LogLevel EagleEye::default_log_level_parser(std::string level)
{
    static const std::unordered_map<std::string, LogLevel> s_level_names_map = {
            {"verbose", LogLevel::verbose},
            {"debug", LogLevel::debug},
            {"info", LogLevel::info},
            {"warning", LogLevel::warning},
            {"error", LogLevel::error}
    };

    // FIXME: provide decent to_lower() implementation. Only ASCII is supported for now.
    std::transform(level.begin(), level.end(), level.begin(), ::tolower);

    auto iter = s_level_names_map.find(level);
    if (iter == s_level_names_map.end())
    {
        throw std::runtime_error(utils::concat_strs("Invalid log level: ", level));
    }
    return iter->second;
}

std::ostream& EagleEye::operator<<(std::ostream& stream, LogLevel level)
{
    stream << std::setw(7);
    switch (level)
    {
    case LogLevel::verbose:
        stream << "VERBOSE";
        break;
    case LogLevel::debug:
        stream << "DEBUG";
        break;
    case LogLevel::info:
        stream << "INFO";
        break;
    case LogLevel::warning:
        stream << "WARNING";
        break;
    case LogLevel::error:
        stream << "ERROR";
        break;
    }
    return stream;
}
