//
// Created by oleg on 8/8/18.
//

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <unordered_map>

#include "actions/ActionsParser.hpp"
#include "parsers/PythonFormatParser.hpp"
#include "LogsParser.hpp"

#include "Utils.hpp"

using namespace EagleEye;
using namespace EagleEye::actions;

std::vector<LogEntry> parse_entries(const std::vector<std::string>& filenames, IFormatParser& format_parser)
{
    std::vector<LogEntry> entries;
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
    return entries;
}

struct Context
{
    explicit Context(std::vector<std::string> filenames, IFormatParser& format_parser)
            : filenames(std::move(filenames)),
              format_parser(format_parser),
              original_manager(parse_entries(this->filenames, format_parser)),
              current_manager(original_manager)
    {

    }

    std::vector<std::string> filenames;
    IFormatParser& format_parser;
    const LogsManager original_manager;
    LogsManager current_manager;
};

typedef std::function<void(Context& context, const std::vector<std::string>& args)> command_t;
class exit_exception : public std::exception
{};

const std::unordered_map<std::string, std::string> g_commands_help = {
        {"help", "Print this help"},
        {"exit", "Exit the interpreter"},
        {"show", "Show current log entries"},
        {"count", "Show the number of current log entries"},
        {"clear", "Remove all filters and sorters from the log entries"},
        {"cmd", "Apply a filter or a sorter to the current log entries"}
};

const std::unordered_map<std::string, command_t> g_commands = {
        {"help", [](Context& context, const std::vector<std::string>& args)
                 {
                     if (args.empty())
                     {
                         for (const auto& [command, help] : g_commands_help)
                         {
                             std::cout << command << " - " << help << std::endl;
                         }
                     }
                     else
                     {
                         for (const auto& cmd : args)
                         {
                             auto iter = g_commands_help.find(cmd);
                             if (iter == g_commands_help.end())
                             {
                                 std::cout << cmd << ": No such command" << std::endl;
                                 continue;
                             }
                             std::cout << cmd << ": " << iter->second << std::endl;
                         }
                     }
                 }},
        {"exit", [](Context& context, const std::vector<std::string>& args)
                 {
                     throw exit_exception();
                 }},
        {"show", [](Context& context, const std::vector<std::string>& args)
                 {
                     std::cout << context.current_manager << std::endl;
                 }},
        {"count", [](Context& context, const std::vector<std::string>& args)
                 {
                     std::cout << context.current_manager.entries().size() << std::endl;
                 }},
        {"clear", [](Context& context, const std::vector<std::string>& args)
                 {
                     context.current_manager = context.original_manager;
                 }},
        {"cmd", [](Context& context, const std::vector<std::string>& args)
                  {
                      auto action = actions::parse_action(args, context.format_parser);
                      action->perform(context.current_manager);
                  }}
};

std::istream& read_command(std::istream& stream,
                           std::string& command,
                           std::vector<std::string>& args)
{
    std::vector<std::string> words;
    if (!utils::read_words(stream, words))
    {
        return stream;
    }

    if (words.empty())
    {
        throw std::runtime_error("Command is empty");
    }

    command = words.front();
    args.assign(words.begin() + 1, words.end());

    return stream;
}

int main(int argc, const char* const argv[])
{
    try
    {
        if (argc < 2)
        {
            throw std::runtime_error("Log file or directory should be specified");
        }
        PythonFormatParser format_parser;
        Context context(std::vector<std::string>(argv + 1, argv + argc), format_parser);

        std::cout << "> ";
        std::string command;
        std::vector<std::string> args;
        while (read_command(std::cin, command, args))
        {
            try
            {
                auto iter = g_commands.find(command);
                if (iter != g_commands.end())
                {
                    iter->second(context, args);
                }
                else
                {
                    std::cout << "Invalid command: " << command << std::endl;
                }
            }
            catch (const exit_exception&)
            {
                std::cout << "Bye." << std::endl;
                break;
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
