#pragma once
#include <sys/file.h>
#include <stdio.h>
#include "CCBaseClass.h"
namespace CCPlatform
{
    class FileLockGuard : non_copyable
    {
    public:
        explicit FileLockGuard(int fd) :
            fd_(fd)
        {
            flock(fd_, LOCK_EX);
        }
        explicit FileLockGuard(FILE* fptr) :
            fptr_(fptr)
        {
            flockfile(fptr_);
        }
        ~FileLockGuard()
        {
            if ( -1 != fd_) {
                flock(fd_, LOCK_UN);
            }

            if ( NULL != fptr_) {
                funlockfile(fptr_);
            }
        }
    private:
        int fd_ = {-1};
        FILE* fptr_ = {NULL};
    };
}
