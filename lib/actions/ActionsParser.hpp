//
// Created by oleg on 8/8/18.
//

#ifndef EAGLEEYE_ACTIONSPARSER_HPP
#define EAGLEEYE_ACTIONSPARSER_HPP

#include <iosfwd>
#include <memory>

#include "IAction.hpp"
#include "IFormatParser.hpp"

namespace EagleEye::actions
{

std::unique_ptr<IAction> parse_action(const std::vector<std::string>& tokens,
                                      const IFormatParser& format_parser);

}

#endif //EAGLEEYE_ACTIONSPARSER_HPP
