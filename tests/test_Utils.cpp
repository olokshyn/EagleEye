//
// Created by oleg on 8/13/18.
//

#include "gtest/gtest.h"

#include "Utils.hpp"

using namespace EagleEye;
using namespace EagleEye::utils;

TEST(Utils, ReadUnitedLine1)
{
    std::string data = "This is one-liner";
    std::stringstream stream(data);
    std::string line;
    EXPECT_TRUE(read_united_line(stream, line));
    EXPECT_EQ(data, line);
}

TEST(Utils, ReadUnitedLine2)
{
    std::string data = "This is two-liner\n"
                       "string, read only first line";
    std::stringstream stream(data);
    std::string line;
    EXPECT_TRUE(read_united_line(stream, line));
    EXPECT_EQ(data.substr(0, data.find('\n')), line);
}

TEST(Utils, ReadUnitedLine3)
{
    std::string data = "This is two-liner \\\n"
                       "but the first two lines should be read\n"
                       "and not this one";
    std::stringstream stream(data);
    std::string line;
    EXPECT_TRUE(read_united_line(stream, line));
    EXPECT_EQ("This is two-liner but the first two lines should be read", line);
}

TEST(Utils, ReadUnitedLine4)
{
    std::string data = "This is three-liner \\\n"
                       "\n"
                       "With two empty lines \\\n"
                       "\n"
                       "Among them.";
    std::stringstream stream(data);
    std::string line;
    EXPECT_TRUE(read_united_line(stream, line));
    EXPECT_EQ("This is three-liner With two empty lines Among them.", line);
}

TEST(Utils, ReadUnitedLine5)
{
    std::string data = "This 'is one-liner with' quotes\n";
    std::stringstream stream(data);
    std::string line;
    EXPECT_TRUE(read_united_line(stream, line));
    EXPECT_EQ(data.substr(0, data.rfind('\n')), line);
}

TEST(Utils, ReadUnitedLine6)
{
    std::string data = "This 'is two-liner \n"
                       "but the first' two lines should be read\n"
                       "and not this one";
    std::stringstream stream(data);
    std::string line;
    EXPECT_TRUE(read_united_line(stream, line));
    EXPECT_EQ("This 'is two-liner but the first' two lines should be read", line);
}

TEST(Utils, ReadUnitedLine7)
{
    std::string data = "This is 'three-liner \n"
                       "\n"
                       "With' two 'empty lines \n"
                       "\n"
                       "Among' them.";
    std::stringstream stream(data);
    std::string line;
    EXPECT_TRUE(read_united_line(stream, line));
    EXPECT_EQ("This is 'three-liner With' two 'empty lines Among' them.", line);
}

TEST(Utils, ReadWords1)
{
    std::string data = "This is one-liner\n";
    std::stringstream stream(data);
    std::vector<std::string> words;
    EXPECT_TRUE(read_words(stream, words));
    EXPECT_EQ(std::vector<std::string>({"This", "is", "one-liner"}), words);
}

TEST(Utils, ReadWords2)
{
    std::string data = "This is two-liner \\\n"
                       "but the first two lines should be read\n"
                       "and not this one";
    std::stringstream stream(data);
    std::vector<std::string> words;
    EXPECT_TRUE(read_words(stream, words));
    EXPECT_EQ(std::vector<std::string>({"This", "is", "two-liner",
                                        "but", "the", "first", "two",
                                        "lines", "should", "be", "read"}), words);
}

TEST(Utils, ReadWords3)
{
    std::string data = "This 'is one-liner with' quotes";
    std::stringstream stream(data);
    std::vector<std::string> words;
    EXPECT_TRUE(read_words(stream, words));
    EXPECT_EQ(std::vector<std::string>({"This", "is one-liner with", "quotes"}), words);
}

TEST(Utils, ReadWords4)
{
    std::string data = "This 'is three-liner with' 'quotes \n"
                       "\n"
                       "That span multi lines \n"
                       "And end here' followed by \\\n"
                       "The next line.";
    std::stringstream stream(data);
    std::vector<std::string> words;
    EXPECT_TRUE(read_words(stream, words));
    EXPECT_EQ(std::vector<std::string>({"This", "is three-liner with",
                                        "quotes That span multi lines And end here",
                                        "followed", "by", "The", "next", "line."}), words);
}
