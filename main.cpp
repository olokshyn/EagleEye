#include <string>
#include <sstream>
#include <iostream>

#include "LogsManager.hpp"
#include "LogsParser.hpp"
#include "parsers/PythonFormatParser.hpp"

using namespace EagleEye;

int main()
{
    try
    {
        return 0;
    }
    catch (const std::exception& exc)
    {
        std::cerr << "Exception: " << exc.what() << std::endl;
    }
    return 1;
}