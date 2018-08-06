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
                "2018-06-11 14:14:06,814 INFO     HTTP code 401 not in retryable HTTP codes for call "
                "'_download_file(https://sync-murraycompany.egnyte.com/v5/get_workgroup_info, ...)'. Re-raising ...\n"
                "2018-06-16 09:48:26,389 WARNING  Try #1 failed for call: "
                "'_download_file(https://sync-murraycompany.egnyte.com/v5/get_workgroup_info, ...)' "
                "with error http_code: -28 [Resolving timed out after 30001 milliseconds] (response_header = {})\n";

        std::stringstream stream(test_input);
        LogsManager manager(stream, PythonFormatParser());
        std::cout << manager << std::endl;

        std::cout << manager.filtered(filters::by_level(LogLevel::warning)) << std::endl;
        std::cout << manager.sorted(sorters::by_level) << std::endl;

        return 0;
    }
    catch (const std::exception& exc)
    {
        std::cerr << "Exception: " << exc.what() << std::endl;
    }
    return 1;
}