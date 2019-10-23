#include "CCTimeInfo.h"
namespace CCPlatform
{
    bool is_leap_year(uint32_t year)
    {
        return ((year % 400) == 0) || ((year % 4 == 0) && (year % 100 != 0));
    }
}