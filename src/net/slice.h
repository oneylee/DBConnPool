#include <string>
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

    Slice EatWord();
    Slice EatLine();
    Slice Eat(size_t n) {
        _end += n;
        return *this;
    }

    inline char operator[](size_t n) const { return _start[n]; }
    std::string ToString() const { return std::string(_start, _end); }
    bool StartWith(Slice& sc) const { return Size() >= sc.Size() && memcmp(_start, sc.Data(), sc.Size()) == 0; }
    bool EndWith(Slice& sc) const { return Size() >= sc.Size() && memcmp(_start + Size() - sc.Size(), sc.Data(), sc.Size()) == 0; }


private:
    const char* _start;
    const char* _end;
};
}