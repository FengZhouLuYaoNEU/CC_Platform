#pragma once
#include <ctime>
#include <cstdint>
#include <string>
using std::uint32_t;
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
    // Method:    ms_timestamp_to_str_date
    // FullName:  CCPlatform::ms_timestamp_to_str_date
    // Access:    public 
    // Returns:   std::string
    // Qualifier:
    // Parameter: std::uint64_t timestamp
    //************************************
    std::string ms_timestamp_to_str_date(std::uint64_t timestamp);
    //************************************
    // Method:    us_timestamp_to_str_date
    // FullName:  CCPlatform::us_timestamp_to_str_date
    // Access:    public 
    // Returns:   std::string
    // Qualifier:
    // Parameter: std::uint64_t timestamp
    //************************************
    std::string us_timestamp_to_str_date(std::uint64_t timestamp);
}
