#include "CCTimeInfo.h"
#include <cstring>
namespace CCPlatform
{
    bool is_leap_year(uint32_t year)
    {
        return ((year % 400) == 0) || ((year % 4 == 0) && (year % 100 != 0));
    }

    std::string s_timestamp_to_str_date(uint64_t timestamp)
    {
        std::time_t time_tick = (std::time_t)timestamp;
        std::tm* time_info_ptr = std::localtime(&time_tick);
        if (NULL == time_info_ptr) {
            return std::string("");
        }
        char buf[128] = {0};
        std::strftime(buf, sizeof(buf), "%Y-%m-%d:%H:%M:%S", time_info_ptr);
        return std::string(buf);
    }

    std::string ms_timestamp_to_str_date(uint64_t timestamp)
    {
        std::uint64_t mill_seconds = timestamp % 1000;
        std::time_t time_tick = (std::time_t)(timestamp / 1000);
        std::tm* time_info_ptr = std::localtime(&time_tick);
        if (NULL == time_info_ptr) {
            return std::string("");
        }
        char buf[128] = {0};
        std::strftime(buf, sizeof(buf), "%Y-%m-%d:%H:%M:%S", time_info_ptr);
        std::snprintf(buf + std::strlen(buf), 3, ".%03lu", mill_seconds);
        return std::string(buf);
    }
}
