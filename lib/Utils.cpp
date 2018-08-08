//
// Created by oleg on 8/8/18.
//

#include "Utils.hpp"

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
        std::unique_ptr<DIR, decltype(&closedir)> dir_guard(dir, &closedir);
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

