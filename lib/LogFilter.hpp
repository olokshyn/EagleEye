//
// Created by oleg on 8/6/18.
//

#ifndef EAGLEEYE_LOGFILTER_HPP
#define EAGLEEYE_LOGFILTER_HPP

#include <functional>

#include "LogEntry.hpp"
#include "LogLevel.hpp"

namespace EagleEye::filters
{

typedef std::function<bool(const LogEntry&)> log_filter_t;

log_filter_t by_level(LogLevel level);

}

#endif //EAGLEEYE_LOGFILTER_HPP
