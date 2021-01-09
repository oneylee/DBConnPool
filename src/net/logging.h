#pragma once
#include <string>
#include "singleton.h"

namespace orz
{
class Logging
{
public:
    enum LEVEL {FATAL, ERROR, WARN, INFO, DEBUG, ALL};
    bool Logv(LEVEL level, const char* filename, int line, const char* func, const char* fmt, ...);
    LEVEL GetLevel() const { return _level; }

private:
    DISALLOW_COPY_AND_ASSIGN(Logging);
    std::string _filename;
    LEVEL _level;
    int _fd;
};
}

#define hlog(level, ...)                                                                                    \
do {                                                                                                        \
    if (level <= orz::Singleton<orz::Logging>::GetInstance().GetLevel()) {                                  \
        orz::Singleton<orz::Logging>::GetInstance().Logv(level, __FILE__, __LINE__, __func__, __VA_ARGS__); \
    }                                                                                                       \
} while(0)

#define debug(...) hlog(orz::Logging::DEBUG, __VA_ARGS__)
#define info(...)  hlog(orz::Logging::INFO,  __VA_ARGS__)
#define warn(...)  hlog(orz::Logging::WARN,  __VA_ARGS__)
#define error(...) hlog(orz::Logging::ERROR, __VA_ARGS__)
#define fatal(...) hlog(orz::Logging::FATAL, __VA_ARGS__)

int test()
{
    orz::Singleton<orz::Logging>::GetInstance()->GET();
    
}