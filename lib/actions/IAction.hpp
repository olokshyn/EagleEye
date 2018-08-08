//
// Created by oleg on 8/8/18.
//

#ifndef EAGLEEYE_IACTION_HPP
#define EAGLEEYE_IACTION_HPP

#include "LogsManager.hpp"

namespace EagleEye::actions
{

class IAction
{
public:
    virtual ~IAction() = default;

    virtual void perform(LogsManager& manager) const = 0;
};

}

#endif //EAGLEEYE_IACTION_HPP
