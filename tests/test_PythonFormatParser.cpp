//
// Created by oleg on 8/7/18.
//

#include <string>
#include <sstream>
#include <chrono>

#include "gtest/gtest.h"

#include "parsers/PythonFormatParser.hpp"
#include "LogsParser.hpp"

using namespace EagleEye;
using date_time::operator==;

TEST(PythonFormatParser, Simple)
{
    const std::string logs = "2018-06-11 14:14:06,814 INFO     This is information message";
    std::stringstream stream(logs);
    auto entries = parser::parse_logs(stream, PythonFormatParser());
    EXPECT_EQ(1, entries.size());
    EXPECT_EQ(LogLevel::info, entries[0].level);
    EXPECT_TRUE("2018-06-11 14:14:06" == entries[0].date_time);
    EXPECT_EQ("This is information message", entries[0].message);
}
