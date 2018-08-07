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

TEST(PythonFormatParser, Simple1)
{
    const std::string logs = "2018-08-07 09:14:06,814 INFO     This is information message";
    std::stringstream stream(logs);
    auto entries = parser::parse_logs(stream, PythonFormatParser());
    EXPECT_EQ(1, entries.size());
    EXPECT_EQ(LogLevel::info, entries[0].level);
    EXPECT_TRUE("2018-08-07 09:14:06" == entries[0].date_time);
    EXPECT_EQ("This is information message", entries[0].message);
}

TEST(PythonFormatParser, Simple2)
{
    const std::string logs = "2018-11-07 09:14:06,000 DEBUG The debug message";
    std::stringstream stream(logs);
    auto entries = parser::parse_logs(stream, PythonFormatParser());
    EXPECT_EQ(1, entries.size());
    EXPECT_EQ(LogLevel::debug, entries[0].level);
    EXPECT_TRUE("2018-11-07 09:14:06" == entries[0].date_time);
    EXPECT_EQ("The debug message", entries[0].message);
}

TEST(PythonFormatParser, TwoLines)
{
    const std::string logs =
            "2018-01-03 02:06:03,030 VERBOSE Some really long log messages that is too long to fit on the screen\n"
            "2018-11-07 09:14:06,000 ERROR A problem happend, so you are going to spend next several days for searching and fixing\n";
    std::stringstream stream(logs);
    auto entries = parser::parse_logs(stream, PythonFormatParser());
    EXPECT_EQ(2, entries.size());

    EXPECT_EQ(LogLevel::verbose, entries[0].level);
    EXPECT_TRUE("2018-01-03 02:06:03" == entries[0].date_time);
    EXPECT_EQ("Some really long log messages that is too long to fit on the screen",
              entries[0].message);

    EXPECT_EQ(LogLevel::error, entries[1].level);
    EXPECT_TRUE("2018-11-07 09:14:06" == entries[1].date_time);
    EXPECT_EQ("A problem happend, so you are going to spend next several days for searching and fixing",
              entries[1].message);
}

TEST(PythonFormatParser, MultiLines)
{
    const std::string logs =
            "2222-01-03 02:06:03,030 WARNING \t\t  The first message\n"
            "1995-10-28 02:40:00,000 INFO        The second message\n"
            "1990-01-01 00:00:00,000 DEBUG The third message          \n"
            "2018-01-01 00:00:00,000 WARNING        The fourth message          \n"
            "2018-01-01 00:00:00,000 INFO Some really long log messages that is too long to fit on the screen\n"
            "2018-01-03 00:00:00,000 DEBUG Another message text \n"
            "2018-01-03 02:00:00,000 INFO \n"
            "2018-11-07 09:14:00,000 ERROR A problem happend, so you are going to spend next several days for searching and fixing\n"
            "2018-01-03 04:16:03,000 VERBOSE \n"
            "2018-01-03 04:16:03,030 VERBOSE No endline on the last line";
    std::stringstream stream(logs);
    auto entries = parser::parse_logs(stream, PythonFormatParser());
    EXPECT_EQ(10, entries.size());

    EXPECT_EQ(LogLevel::warning, entries[0].level);
    EXPECT_TRUE("2222-01-03 02:06:03" == entries[0].date_time);
    EXPECT_EQ("The first message",
              entries[0].message);

    EXPECT_EQ(LogLevel::info, entries[1].level);
    EXPECT_TRUE("1995-10-28 02:40:00" == entries[1].date_time);
    EXPECT_EQ("The second message",
              entries[1].message);

    EXPECT_EQ(LogLevel::debug, entries[2].level);
    EXPECT_TRUE("1990-01-01 00:00:00" == entries[2].date_time);
    EXPECT_EQ("The third message          ",
              entries[2].message);

    EXPECT_EQ(LogLevel::warning, entries[3].level);
    EXPECT_TRUE("2018-01-01 00:00" == entries[3].date_time);
    EXPECT_EQ("The fourth message          ",
              entries[3].message);

    EXPECT_EQ(LogLevel::info, entries[4].level);
    EXPECT_TRUE("2018-01-01 00:00:00" == entries[4].date_time);
    EXPECT_EQ("Some really long log messages that is too long to fit on the screen",
              entries[4].message);

    EXPECT_EQ(LogLevel::debug, entries[5].level);
    EXPECT_TRUE("2018-01-03 00:00:00" == entries[5].date_time);
    EXPECT_EQ("Another message text ",
              entries[5].message);

    EXPECT_EQ(LogLevel::info, entries[6].level);
    EXPECT_TRUE("2018-01-03 02:00:00" == entries[6].date_time);
    EXPECT_EQ("",
              entries[6].message);

    EXPECT_EQ(LogLevel::error, entries[7].level);
    EXPECT_TRUE("2018-11-07 09:14:00" == entries[7].date_time);
    EXPECT_EQ("A problem happend, so you are going to spend next several days for searching and fixing",
              entries[7].message);

    EXPECT_EQ(LogLevel::verbose, entries[8].level);
    EXPECT_TRUE("2018-01-03 04:16:03" == entries[8].date_time);
    EXPECT_EQ("",
              entries[8].message);

    EXPECT_EQ(LogLevel::verbose, entries[9].level);
    EXPECT_TRUE("2018-01-03 04:16:03" == entries[9].date_time);
    EXPECT_EQ("No endline on the last line",
              entries[9].message);
}
