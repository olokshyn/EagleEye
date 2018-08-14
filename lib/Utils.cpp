//
// Created by oleg on 8/8/18.
//

#include "Utils.hpp"

#include <sys/stat.h>

#include <dirent.h>
#include <string.h>

#include <iterator>
#include <algorithm>
#include <memory>

using namespace EagleEye;

std::vector<std::string> utils::files_in_dir(const std::string& dirpath)
{
//    std::vector<fs::directory_entry> files;
//    std::copy_if(fs::directory_iterator(dirpath),
//                 fs::directory_iterator(),
//                 std::back_inserter(files),
//                 [](const auto& entry) -> bool { return entry.is_regular_file(); });
//    std::vector<std::string> filenames;
//    filenames.reserve(files.size());
//    std::transform(files.begin(),
//                   files.end(),
//                   std::back_inserter(filenames),
//                   [](const auto& entry) -> std::string { return entry.path; });
//    return filenames;
    // FIXME: fucking GCC 7 does not fully support C++17 std::filesystem, so remove this crap when std::filesystem is available.
    std::vector<std::string> filenames;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(dirpath.c_str())))
    {
        auto destructor = [](DIR* dir) { closedir(dir); };
        std::unique_ptr<DIR, decltype(destructor)> dir_guard(dir, destructor);
        while ((ent = readdir(dir)))
        {
            if (ent->d_type == DT_REG)
            {
                filenames.push_back(concat_strs(dirpath, "/", ent->d_name));
            }
            else if (ent->d_type == DT_UNKNOWN)
            {
                throw std::runtime_error(concat_strs("Unknown direntry: ", ent->d_name));
            }
        }
    }
    else
    {
        throw std::runtime_error(concat_strs("Failed to open directory: ", strerror(errno)));
    }
    return filenames;
}

std::string utils::file_basename(const std::string& path)
{
    // FIXME: replace this crap with std::filesystem.
    auto pos = path.rfind('/');
    if (pos == std::string::npos)
    {
        return path;
    }
    return path.substr(pos + 1);
}

bool utils::is_dir(const std::string& dirname)
{
    // FIXME: replace this crap with std::filesystem
    struct stat st = {};
    if (stat(dirname.c_str(), &st) == 0)
    {
        return static_cast<bool>(st.st_mode & S_IFDIR);
    }
    throw std::system_error();
}

std::istream& utils::read_united_line(std::istream& stream, std::string& line)
{
    std::stringstream united_stream;
    bool next_line_needed = true;
    size_t quotations_count = 0;
    size_t united_line_size = 0;

    std::string curr_line;
    while (next_line_needed && std::getline(stream, curr_line))
    {
        united_stream << curr_line;
        quotations_count += std::count(curr_line.begin(), curr_line.end(), '\'');
        united_line_size += curr_line.size();
        if (!curr_line.empty() && curr_line.back() == '\\')
        {
            --united_line_size;
        }
        next_line_needed = curr_line.empty() || quotations_count % 2 || curr_line.back() == '\\';
    }

    line.clear();
    line.reserve(united_line_size);
    std::copy_if(std::istreambuf_iterator<char>(united_stream),
                 std::istreambuf_iterator<char>(),
                 std::back_inserter(line),
                 [](auto symbol) -> bool { return symbol != '\\'; });
    return stream;
}

std::istream& utils::read_words(std::istream& stream, std::vector<std::string>& words)
{
    std::string line;
    if (!(read_united_line(stream, line)))
    {
        return stream;
    }

    bool inside_quotations = false;
    size_t start = 0;
    while (start != std::string::npos)
    {
        size_t end = line.find('\'', start);

        std::string token(line.substr(start, end - start));
        if (inside_quotations)
        {
            words.push_back(token);
        }
        else
        {
            std::stringstream s_stream(token);
            std::string word;
            while (s_stream >> word)
            {
                words.push_back(word);
            }
        }

        if (end != std::string::npos)
        {
            start = end + 1;
        }
        else
        {
            start = end;
        }
        inside_quotations = !inside_quotations;
    }

    return stream;
}
