#include "CCTimeInfo.h"
#include <cstring>
#include <stdexcept>
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
        std::strftime(buf, sizeof(buf), "%Y-%m-%d_%H:%M:%S", time_info_ptr);
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
        std::strftime(buf, sizeof(buf), "%Y-%m-%d_%H:%M:%S", time_info_ptr);
        std::snprintf(buf + std::strlen(buf), 3, ".%03lu", mill_seconds);
        return std::string(buf);
    }

    std::string get_next_day(const std::string& cur_day)
    {
        if (cur_day.size() < 8) {
            return std::string("");
        }
        int year = 0, month = 0, day = 0;
        try {
            year = std::stoi(cur_day.substr(0, 4));
            month = std::stoi(cur_day.substr(5, 2));
            day = std::stoi(cur_day.substr(8, 2));
        }
        catch (std::invalid_argument) {
            return std::string("");
        }
        int year_addend = 0, day_limit = 0;
        switch (month) {
            case 12:
            {
                year_addend = 1; day_limit = 31;
            }
            break;
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            {
                year_addend = 0; day_limit = 31;
            }
            break;
            case 4:
            case 6:
            case 9:
            case 11:
            {
                year_addend = 0; day_limit = 30;
            }
            break;
            case 2:
            {
                year_addend = 0;
                day_limit = is_leap_year(year) ? 29 : 28;
            }
            break;
            default:
            {
                return std::string("");
            }
            break;
        }

        if (day_limit == day) {
            year += year_addend;
            month += 1;
            if (13 == month) {
                month = 1;
            }
            day = 1;
        }
        else if (day < day_limit) {
            day += 1;
        }
        else {
            return std::string("");
        }
        char buf[64] = {0};
        std::snprintf(buf, sizeof(buf), "%04d-%02d-%02d", year, month, day);
        return std::string(buf);
    }

    std::string get_last_day(const std::string& cur_day)
    {
        if (cur_day.size() < 8) {
            return std::string("");
        }
        int year = 0, month = 0, day = 0;
        try {
            year = std::stoi(cur_day.substr(0, 4));
            month = std::stoi(cur_day.substr(5, 2));
            day = std::stoi(cur_day.substr(8, 2));
        }
        catch (std::invalid_argument) {
            return std::string("");
        }
        int limit_day = is_leap_year(year) ? 29 : 28;
        switch (month) {
            case 1:
            {
                if (1 == day) {
                    year -= 1; month = 12; day = 31;
                }
                else if (day <= 31) {
                    day -= 1;
                }
                else {
                    return std::string("");
                }
            }
            break;
            case 3:
            {
                if (1 == day) {
                    month = 2; day = limit_day;
                }
                else if (day <= 31) {
                    day -= 1;
                }
                else {
                    return std::string("");
                }
            }
            break;
            case 12:
            case 10:
            case 7:
            case 5:
            {
                if (1 == day) {
                    day = 30; month -= 1;
                }
                else if (day <= 31) {
                    day -= 1;
                }
                else {
                    return std::string("");
                }
            }
            break;
            case 8:
            {
                if (1 == day) {
                    day = 31; month = 7;
                }
                else if (day <= 31) {
                    day -= 1;
                }
                else {
                    return std::string("");
                }
            }
            break;
            case 2:
            {
                if (1 == day) {
                    day = 31; month = 1;
                }
                else if (day <= limit_day) {
                    day -= 1;
                }
                else {
                    return std::string("");
                }
            }
            break;
            case 4:
            case 6:
            case 9:
            case 11:
            {
                if (1 == day) {
                    day = 31; month -= 1;
                }
                else if (day <= 30) {
                    day -= 1;
                }
                else {
                    return std::string("");
                }
            }
            break;
            default:
            {
                return std::string("");
            }
            break;
        }
        char buf[64] = {0};
        std::snprintf(buf, sizeof(buf), "%04d-%02d-%02d", year, month, day);
        return std::string(buf);
    }

    uint64_t str_date_to_s_timestamp(const std::string& date)
    {
        uint64_t timestamp = 0;
        return timestamp;
    }

    uint64_t str_date_to_ms_timestamp(const std::string& date)
    {
        uint64_t timestamp = 0;
        return timestamp;
    }
}
