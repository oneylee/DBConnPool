#pragma once
#include <stdint.h>

namespace orz
{
class Util
{
public:
    static uint64_t GetTid();

    static uint64_t GetPid();

    // static char* buf;
    static const char* GetProcessName(uint64_t pid = 0);
};
}