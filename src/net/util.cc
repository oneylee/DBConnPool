#include "util.h"
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>

#include <errno.h>
#include <iostream>

namespace orz
{
static const uint32_t BUF_LEN = 10240;

uint64_t Util::GetTid() {
    return syscall(SYS_gettid);
}

uint64_t Util::GetPid() {
    return getpid();
}

const char* Util::GetProcessName(uint64_t pid) {
    std::string path("/proc/");
    if (pid == 0) {
        path.append("self");
    } else {
        path.append(std::to_string(pid));
    }
    
    path.append("/exe");
    static char* buf = new char[BUF_LEN];
    ssize_t len = readlink(path.data(), buf, BUF_LEN);
    if (len == -1) perror("readlink: ");
    if (len == -1 || len >= BUF_LEN) return "UNKNOWN";

    buf[len] = '\0';
    char* p = &buf[len];
    for ( ; p >= buf; --p) {
        if (*p == '/') {
            p++;
            break;
        }
    }
    return p;
}
}