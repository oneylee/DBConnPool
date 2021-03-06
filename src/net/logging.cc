#include <stdarg.h>
#include <time.h>
#include <iostream>
#include "util.h"
#include "logging.h"

namespace orz
{

const char* Logging::_level_str[] = {"FATAL", "ERROR", "WARN", "INFO", "DEBUG"};

uint64_t Logging::_pid = orz::Util::GetPid();
std::string Logging::_process_name = orz::Util::GetProcessName(_pid);
static thread_local uint64_t tid = orz::Util::GetTid();
bool Logging::Logv(LEVEL level, const char* filename, int line, const char* func, const char* fmt...) {
    if (level > _level) return true;
    

    char buf[4096];
    char* start = buf;
    char* end = buf + 4096;

    time_t tt = time(NULL);
    struct tm tm;
    localtime_r(&tt, &tm);

    start += snprintf(start, end - start, "[%4d/%02d/%02d %02d:%02d:%02d]-[%s]-[PID:%d]-[%s] : ", 
        tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, _level_str[_level], 
        _pid, _process_name.data());
    
    va_list al;
    va_start(al, fmt);
    start += snprintf(start, end - start, fmt, al);
    va_end(al);

    start = std::min(start, end - 2);
    while (*--start == '\n') {}
    *++start = '\0';
    *++start = '\n';
    std::cout << buf << std::endl;
    return true;

}
}

int main()
{
    info("ccc%d", 12);
    return 0;
}