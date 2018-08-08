//
// Created by oleg on 8/8/18.
//

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>

#include "actions/ActionsParser.hpp"
#include "parsers/PythonFormatParser.hpp"
#include "LogsParser.hpp"

#include "Utils.hpp"

using namespace EagleEye;
using namespace EagleEye::actions;

int main(int argc, const char* const argv[])
{
    try
    {
        if (argc < 2)
        {
            throw std::runtime_error("Log file or directory should be specified");
        }

        std::vector<LogEntry> entries;
        PythonFormatParser format_parser;

        std::vector<std::string> filenames(argv + 1, argv + argc);
        if (utils::is_dir(filenames[0]))
        {
            if (filenames.size() > 1)
            {
                throw std::runtime_error("Currently only one directory is supported");
            }
            entries = parser::parse_logs_dir(filenames[0], format_parser);
        }
        else
        {
            entries = parser::parse_logs(filenames, format_parser);
        }

        LogsManager original_manager(std::move(entries));
        LogsManager current_manager(original_manager);

        std::cout << "> ";
        std::string command;
        while (std::getline(std::cin, command))
        {
            try
            {
                if (command == "exit")
                {
                    break;
                }
                else if (command == "show")
                {
                    std::cout << current_manager << std::endl;
                }
                else if (command == "clear")
                {
                    current_manager = original_manager;
                }
                else
                {
                    std::stringstream action_stream(command);
                    auto actions = actions::parse_actions(action_stream, format_parser);
                    for (const auto& action : actions)
                    {
                        action->perform(current_manager);
                    }
                }
            }
            catch (const std::exception& exc)
            {
                std::cerr << "Exception: " << exc.what() << std::endl;
            }
            std::cout << "> ";
        }

        return 0;
    }
    catch (const std::exception& exc)
    {
        std::cerr << "Exception: " << exc.what() << std::endl;
        return 1;
    }
}
