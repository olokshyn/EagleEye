//
// Created by oleg on 8/8/18.
//

#include "SortingAciton.hpp"

using namespace EagleEye::actions;

SortingAciton::SortingAciton(sorters::log_sorter_t sorter)
        : m_sorter(std::move(sorter))
{

}

void SortingAciton::perform(LogsManager& manager) const
{
    manager.sort(m_sorter);
}
