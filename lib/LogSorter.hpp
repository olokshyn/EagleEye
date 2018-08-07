//
// Created by oleg on 8/6/18.
//

#ifndef EAGLEEYE_LOGSORTER_HPP
#define EAGLEEYE_LOGSORTER_HPP

#include <functional>

#include "LogEntry.hpp"

namespace EagleEye::sorters
{

typedef std::function<bool(const LogEntry&, const LogEntry&)> log_sorter_t;

log_sorter_t by_level(bool ascending = false);

log_sorter_t by_date_time(bool ascending = true);

}

#endif //EAGLEEYE_LOGSORTER_HPP
