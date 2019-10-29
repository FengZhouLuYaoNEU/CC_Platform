#pragma once
#include <linux/limits.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "CCErrorNo.h"
namespace CCPlatform
{
    //************************************
    // Method:    mkdirs
    // FullName:  CCPlatform::mkdirs
    // Access:    public 
    // Returns:   bool
    // Qualifier:
    // Parameter: const char * muldir
    //************************************
    bool mkdirs(const char* muldir);
}
