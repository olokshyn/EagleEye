//
// Created by oleg on 8/8/18.
//

#ifndef EAGLEEYE_ACTIONSPARSER_HPP
#define EAGLEEYE_ACTIONSPARSER_HPP

#include <iosfwd>
#include <memory>
#include <list>

#include "IAction.hpp"
#include "IFormatParser.hpp"

namespace EagleEye::actions
{

std::list<std::unique_ptr<IAction>> parse_actions(std::istream& stream,
                                                  const IFormatParser& format_parser);

}

#endif //EAGLEEYE_ACTIONSPARSER_HPP
