//
// Created by oleg on 8/8/18.
//

#ifndef EAGLEEYE_FILTERINGACTION_HPP
#define EAGLEEYE_FILTERINGACTION_HPP

#include "IAction.hpp"
#include "LogFilter.hpp"

namespace EagleEye::actions
{

class FilteringAction : public IAction
{
public:
    explicit FilteringAction(filters::log_filter_t filter);

    void perform(LogsManager& manager) const override;

private:
    filters::log_filter_t m_filter;
};

}

#endif //EAGLEEYE_FILTERINGACTION_HPP
