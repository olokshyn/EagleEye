//
// Created by oleg on 8/6/18.
//

#ifndef EAGLEEYE_UTILS_HPP
#define EAGLEEYE_UTILS_HPP

#include <string>
#include <sstream>

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

}

#endif //EAGLEEYE_UTILS_HPP
