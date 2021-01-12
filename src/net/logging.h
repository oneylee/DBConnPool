#pragma once
#include <string>
#include "singleton.h"

namespace orz
{
class Logging
{
public:
    enum LEVEL {FATAL, ERROR, WARN, INFO, DEBUG};
    enum TYPE {CONSOLE, FILE, ALL};

    Logging() : _level(DEBUG), _type(FILE) {}
    ~Logging() {}

    bool Logv(LEVEL level, const char* filename, int line, const char* func, const char* fmt...);
    LEVEL GetLevel() const { return _level; }
    bool SetLevel(LEVEL level) { _level = level; return true; }
    bool SetType(TYPE type) { _type = type; return true; }
    bool SetFilename(const std::string& filename);

private:
    DISALLOW_COPY_AND_ASSIGN(Logging);
    static const char* _level_str[LEVEL::DEBUG + 1];
    std::string _filename;
    LEVEL _level;
    int _fd;
    static uint64_t _pid;
    static std::string _process_name;
    TYPE _type;
};
}

// #define hlog(level, ...)                                                                                    \
// do {                                                                                                        \
//     if (level <= orz::Singleton<orz::Logging>::GetInstance().GetLevel()) {                                  \
//         orz::Singleton<orz::Logging>::GetInstance().Logv(level, __FILE__, __LINE__, __func__, __VA_ARGS__); \
//     }                                                                                                       \
// } while(0)
#define hlog(level, ...) orz::Singleton<orz::Logging>::GetInstance()->Logv(level, __FILE__, __LINE__, __func__, __VA_ARGS__)


#define debug(...) hlog(orz::Logging::DEBUG, __VA_ARGS__)
#define info(...)  hlog(orz::Logging::INFO,  __VA_ARGS__)
#define warn(...)  hlog(orz::Logging::WARN,  __VA_ARGS__)
#define error(...) hlog(orz::Logging::ERROR, __VA_ARGS__)
#define fatal(...) hlog(orz::Logging::FATAL, __VA_ARGS__)