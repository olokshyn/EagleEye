//
// Created by oleg on 8/6/18.
//

#include "LogSorter.hpp"

bool EagleEye::sorters::by_level(const LogEntry& left, const LogEntry& right)
{
    return left.level > right.level;
}
