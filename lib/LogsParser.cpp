//
// Created by oleg on 8/7/18.
//

#include "LogsParser.hpp"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <list>

#include "Utils.hpp"

using namespace EagleEye;

namespace
{

long int count_lines(std::ifstream& stream)
{
    auto lines_count = std::count(std::istreambuf_iterator<char>(stream),
                                  std::istreambuf_iterator<char>(),
                                  '\n') + 1l;
    stream.seekg(0);
    return lines_count;
}

}

std::vector<LogEntry> parser::parse_logs(
        std::istream& in, const EagleEye::IFormatParser& format_parser,
        size_t log_entries_hint)
{
    std::vector<LogEntry> entries;
    entries.reserve(log_entries_hint);

    std::string line;
    while (std::getline(in, line))
    {
        try
        {
            entries.push_back(format_parser.parse_line(line));
        }
        catch (const std::exception& exc)
        {
            std::cerr << "Failed to parse line: " << line << " " << exc.what() << std::endl;
        }
    }
    return entries;
}

std::vector<LogEntry> parser::parse_logs(const std::string& filename,
                                         const IFormatParser& format_parser)
{
    std::ifstream stream(filename);
    if (!stream.is_open())
    {
        throw std::runtime_error(utils::concat_strs("Failed to open file: ", filename));
    }
    return parse_logs(stream, format_parser, static_cast<size_t>(count_lines(stream)));
}


std::vector<LogEntry> parser::parse_logs(const std::vector<std::string>& filenames,
                                         const IFormatParser& format_parser)
{
    std::list<std::vector<LogEntry>> chunks;
    for (const auto& filename : filenames)
    {
        chunks.push_back(parse_logs(filename, format_parser));
    }
    auto total_size = std::accumulate(chunks.begin(),
                                      chunks.end(),
                                      std::vector<LogEntry>::size_type(),
                                      [](auto size, const auto& entries)
                                      { return size + entries.size(); });
    std::vector<LogEntry> collected_entries;
    collected_entries.reserve(total_size);
    for (auto& entries : chunks)
    {
        for (auto& entry : entries)
        {
            collected_entries.push_back(std::move(entry));
        }
    }
    return collected_entries;
}

std::vector<LogEntry> parser::parse_logs_dir(const std::string& dirname,
                                             const IFormatParser& format_parser)
{
    return parse_logs(utils::files_in_dir(dirname), format_parser);
}
