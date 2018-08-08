//
// Created by oleg on 8/8/18.
//

#ifndef EAGLEEYE_SORTINGACITON_HPP
#define EAGLEEYE_SORTINGACITON_HPP

#include "IAction.hpp"
#include "LogSorter.hpp"

namespace EagleEye::actions
{

class SortingAciton : public IAction
{
public:
    explicit SortingAciton(sorters::log_sorter_t sorter);

    void perform(LogsManager& manager) const override;

private:
    sorters::log_sorter_t m_sorter;
};

}

#endif //EAGLEEYE_SORTINGACITON_HPP
