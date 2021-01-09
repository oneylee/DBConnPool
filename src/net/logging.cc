#include <stdarg.h>
#include "logging.h"

namespace orz
{
bool Logging::Logv(LEVEL level, const char* filename, int line, const char* func, const char* fmt, ...) {
    if (level > _level) return true;
    

    char buf[4096];
    char* start = buf;
    char* end = buf + 4096;

    va_list al;
    va_start(al, fmt);

}
}