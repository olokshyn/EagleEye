#include <string>
#include <sstream>
#include <iostream>

#include "LogsManager.hpp"
#include "parsers/PythonFormatParser.hpp"

using namespace EagleEye;

int main()
{
    try
    {
        const std::string test_input =
                "2018-06-11 14:14:06,814 INFO     This is information mesasge\n"
                "2018-06-16 09:48:26,389 WARNING  This is warning message, shit happened here\n";

        std::stringstream stream(test_input);
        LogsManager manager(stream, PythonFormatParser());
        std::cout << manager << std::endl;

        std::cout << manager.filtered(filters::by_level(LogLevel::warning)) << std::endl;
        std::cout << manager.sorted(sorters::by_level()) << std::endl;

        std::cout << manager.filtered(filters::by_message("^This\\s\\w+\\swarning\\s")) << std::endl;

        return 0;
    }
    catch (const std::exception& exc)
    {
        std::cerr << "Exception: " << exc.what() << std::endl;
    }
    return 1;
}