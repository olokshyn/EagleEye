//
// Created by oleg on 8/6/18.
//

#ifndef EAGLEEYE_UTILS_HPP
#define EAGLEEYE_UTILS_HPP

#include <string>
#include <sstream>
#include <vector>

namespace EagleEye::utils
{

template <typename T>
void _concat_strs(std::stringstream& stream, T arg)
{
    stream << arg;
}

template <typename T, typename... Args>
void _concat_strs(std::stringstream& stream, T arg, Args... args)
{
    stream << arg;
    _concat_strs(stream, args...);
}

template <typename... Args>
std::string concat_strs(Args... args)
{
    std::stringstream stream;
    _concat_strs(stream, args...);
    return stream.str();
}

std::vector<std::string> files_in_dir(const std::string& dirpath);
std::string file_basename(const std::string& path);
bool is_dir(const std::string& dirname);

std::istream& read_united_line(std::istream& stream, std::string& line);
std::istream& read_words(std::istream& stream, std::vector<std::string>& words);

}

#endif //EAGLEEYE_UTILS_HPP
