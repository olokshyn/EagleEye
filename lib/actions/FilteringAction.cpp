//
// Created by oleg on 8/8/18.
//

#include "FilteringAction.hpp"

using namespace EagleEye::actions;

FilteringAction::FilteringAction(filters::log_filter_t filter)
        : m_filter(std::move(filter))
{

}

void FilteringAction::perform(LogsManager& manager) const
{
    manager.filter(m_filter);
}