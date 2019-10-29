#pragma once
#include <vector>
#include <string>
#include "CCErrorNo.h"
namespace CCPlatform
{
    int32_t stl_spilt_str(const std::string& str, const std::string& deli, std::vector<std::string>& v);
}
