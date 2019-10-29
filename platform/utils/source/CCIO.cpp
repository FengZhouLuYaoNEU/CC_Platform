#include "CCIO.h"
namespace CCPlatform
{
    bool mkdirs(const char* muldir)
    {
        char str[PATH_MAX] = {0};
        strncpy(str, muldir, sizeof(str));
        uint32_t len = strlen(str);
        for (uint32_t i = 1; i < len; i++) {
            if ('/' == str[i]) {
                str[i] = '\0';
                if (0 != access(str, 0)) {
                    if (-1 == mkdir(str, 0777)) {
                        return false;
                    }
                }
                str[i] = '/';
            }
        }
        if (len > 0 && access(str, 0) != 0) {
            if (-1 == mkdir(str, 0777)) {
                return false;
            }
        }
        return true;
    }
}
