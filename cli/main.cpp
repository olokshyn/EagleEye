//
// Created by oleg on 8/8/18.
//

#include <iostream>
#include <string>
#include <memory>
#include <list>

#include "actions/IAction.hpp"

using namespace EagleEye;
using namespace EagleEye::actions;

struct Options
{
    std::string filename;
    std::string dirname;
    std::list<std::unique_ptr<IAction>> m_actions;
};

void parse_args(int argc, const char* argv[])
{

}

int main(int argc, const char* const argv[])
{
    try
    {

        return 0;
    }
    catch (const std::exception& exc)
    {
        std::cerr << "Exception: " << exc.what() << std::endl;
        return 1;
    }
}
