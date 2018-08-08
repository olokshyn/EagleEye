//
// Created by oleg on 8/6/18.
//

#ifndef EAGLEEYE_LOGLEVEL_HPP
#define EAGLEEYE_LOGLEVEL_HPP

#include <iosfwd>
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

LogLevel log_level_parser(std::string level);

std::ostream& operator<<(std::ostream& stream, LogLevel level);

}

#endif //EAGLEEYE_LOGLEVEL_HPP
