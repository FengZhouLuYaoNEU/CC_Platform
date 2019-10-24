#pragma once
#include <ctime>
#include <cstdint>
#include <string>
using std::uint32_t;
using std::uint64_t;
namespace CCPlatform
{
    //************************************
    // Method:    is_leap_year
    // FullName:  CCPlatform::is_leap_year
    // Access:    public 
    // Returns:   bool
    // Qualifier:
    // Parameter: uint32_t year
    //************************************
    bool is_leap_year(uint32_t year);
    //************************************
    // Method:    s_timestamp_to_str_date
    // FullName:  CCPlatform::s_timestamp_to_str_date
    // Access:    public 
    // Returns:   std::string
    // Qualifier: date format: 2019-05-20_16:55:43
    // Parameter: uint64_t timestamp
    //************************************
    std::string s_timestamp_to_str_date(uint64_t timestamp);
    //************************************
    // Method:    ms_timestamp_to_str_date
    // FullName:  CCPlatform::ms_timestamp_to_str_date
    // Access:    public 
    // Returns:   std::string
    // Qualifier: date format: 2019-05-20_16:55:43.123
    // Parameter: uint64_t timestamp
    //************************************
    std::string ms_timestamp_to_str_date(uint64_t timestamp);
    //************************************
    // Method:    get_next_day
    // FullName:  CCPlatform::get_next_day
    // Access:    public 
    // Returns:   std::string
    // Qualifier: day format: 2019-05-20
    // Parameter: const std::string & cur_day
    //************************************
    std::string get_next_day(const std::string& cur_day);
    //************************************
    // Method:    get_last_day
    // FullName:  CCPlatform::get_last_day
    // Access:    public 
    // Returns:   std::string
    // Qualifier: day format: 2019-05-20
    // Parameter: const std::string & cur_day
    //************************************
    std::string get_last_day(const std::string& cur_day);
    //************************************
    // Method:    str_date_to_s_timestamp
    // FullName:  CCPlatform::str_date_to_s_timestamp
    // Access:    public 
    // Returns:   uint64_t
    // Qualifier: date format: 2019-05-20_16:55:43
    // Parameter: const std::string & date
    //************************************
    uint64_t str_date_to_s_timestamp(const std::string& date);
    //************************************
    // Method:    str_date_to_ms_timestamp
    // FullName:  CCPlatform::str_date_to_ms_timestamp
    // Access:    public 
    // Returns:   uint64_t
    // Qualifier: date format: 2019-05-20_16:55:43.123
    // Parameter: const std::string & date
    //************************************
    uint64_t str_date_to_ms_timestamp(const std::string& date);
}
