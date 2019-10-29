#include "CCString.h"
namespace CCPlatform
{
    int32_t stl_spilt_str(const std::string& str, const std::string& deli, std::vector<std::string>& v)
    {
        if (str.empty() || deli.empty())
        {
            return EMPTY_STRING_ERRNO;
        }
        size_t last = 0;
        size_t index = str.find_first_of(deli, last);
        while (index != std::string::npos) {
            v.push_back(str.substr(last, index - last));
            last = index + 1;
            index = str.find_first_of(deli, last);
        }
        if (index - last > 0) {
            v.push_back(str.substr(last, index - last));
        }
        return SUCCESS;
    }
}
