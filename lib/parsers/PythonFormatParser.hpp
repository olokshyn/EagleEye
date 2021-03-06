//
// Created by oleg on 8/6/18.
//

#ifndef EAGLEEYE_PYTHONFORMATPARSER_HPP
#define EAGLEEYE_PYTHONFORMATPARSER_HPP

#include "IFormatParser.hpp"

namespace EagleEye
{

class PythonFormatParser : public IFormatParser
{
public:
    LogEntry parse_line(const std::string& line) const override;
};

}

#endif //EAGLEEYE_PYTHONFORMATPARSER_HPP
