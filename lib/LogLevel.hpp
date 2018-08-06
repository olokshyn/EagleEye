//
// Created by oleg on 8/6/18.
//

#ifndef EAGLEEYE_LOGLEVEL_HPP
#define EAGLEEYE_LOGLEVEL_HPP

#include <string>
#include <functional>

namespace EagleEye
{

enum class LogLevel
{
    verbose,
    debug,
    info,
    warning,
    error
};

typedef std::function<LogLevel(const std::string&)> log_level_parser_t;

LogLevel default_log_level_parser(std::string level);

}

#endif //EAGLEEYE_LOGLEVEL_HPP
