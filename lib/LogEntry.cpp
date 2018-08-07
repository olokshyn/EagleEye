//
// Created by oleg on 8/6/18.
//

#include "LogEntry.hpp"

#include <ctime>

#include <iostream>

std::ostream& EagleEye::operator<<(std::ostream& stream, const LogEntry& entry)
{
    using date_time::operator<<;
    return stream << entry.date_time << " " << entry.level << " " << entry.message;
}
