#pragma once
#include <string>
#include <vector>
#include <cstring>

namespace orz
{
class Slice
{
public:
    Slice() : _start("") { _end = _start; }
    Slice(const char* start, const char* end) { 
        _start = start; 
        _end = end; 
    }
    Slice(const char* start, size_t len) {
        _start = start;
        _end = _start + len;
    }
    Slice (const std::string& str) {
        _start = str.data();
        _end = _start + str.length();
    }
    Slice (const char* str) {
        _start = str;
        _end = _start + strlen(str);
    }

    const char* Begin() const { return _start; }
    const char* End() const { return _end; }
    const char* Data() const { return _start; }
    size_t Size() const { return _end - _start; }
    char Front() const { return *_start; }
    char Back() const { return _end[-1]; }
    size_t Resize(size_t len) { _end = _start + len; return Size(); }
    bool Empty() const { return _start == _end; }
    bool Clear() { _start = _end = ""; }

    Slice& TrimSpace();
    Slice EatWord();
    Slice EatLine();
    Slice Eat(size_t n) {
        Slice s(_start, n);
        _start += n;
        return s;
    }

    Slice Sub(size_t begin_pos, size_t offset) { 
        Slice s(_start + begin_pos, offset); 
        return s; 
    }

    inline char operator[](size_t n) const { return _start[n]; }

    std::string ToString() const { return std::string(_start, _end); }
    bool StartWith(Slice& sc) const {
        return Size() >= sc.Size() && 
            memcmp(_start, sc.Data(), sc.Size()) == 0; 
    }
    bool EndWith(Slice& sc) const { 
        return Size() >= sc.Size() && 
            memcmp(_start + Size() - sc.Size(), sc.Data(), sc.Size()) == 0; 
    }

    operator std::string() const { return std::string(_start, _end); }
    int Compare(const Slice& sc) const;
    std::vector<Slice> Split(const char& ch) const;


private:
    const char* _start;
    const char* _end;
};

int Slice::Compare(const Slice& sc) const {
    size_t tlen = Size();
    size_t olen = sc.Size();

    size_t sz = tlen > olen ? olen : tlen;

    int r = memcmp(_start, sc.Data(), sz);
    if (r == 0) {
        if (tlen > olen) 
            return 1;
        else if (tlen < olen) 
            return -1;
    }
    return r;
}

Slice& Slice::TrimSpace() {
    while (_start < _end && isspace(*_start)) {
        ++_start;
    }
    while (_start < _end && isspace(_end[-1])) {
        --_end;
    }
    return *this;
}

Slice Slice::EatWord() {
    const char* b = _start;
    while (b < _end && isspace(*b)) {
        ++b;
    }
    const char* e = b;
    while (e < _end && !isspace(*e)) {
        ++e;
    }

    _start = e;
    return Slice(b, e - b);
}

Slice Slice::EatLine() {
    const char* b = _start;
    while (_start <= _end && *_start != '\n') {
        ++_start;
    }
    return Slice(b, _start);
}

std::vector<Slice> Slice::Split(const char& ch) const {
    const char* b = _start;
    std::vector<Slice> result;
    for (const char* bp = _start; bp != _end; ++bp) {
        if (*bp == ch) {
            result.emplace_back(Slice(b, bp));
            b = bp + 1;
        }
    }
    if (b != _end) {
        result.emplace_back(Slice(b, _end));
    }
    return result;
}

inline bool operator<(const Slice& left, const Slice& right) {
    return left.Compare(right) < 0;
}

inline bool operator==(const Slice& left, const Slice& right) {
    return left.Compare(right) == 0;
}

inline bool operator!=(const Slice& left, const Slice& right) {
    return left.Compare(right) != 0;
}
}