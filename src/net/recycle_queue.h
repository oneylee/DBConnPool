#include <stdint.h>
#include <string.h>

namespace orz
{
template<typename T>
class RecycleQueue
{
public:
    RecycleQueue() : _queue(nullptr), _readpos(0), _writepos(0),
                     _dropcount(0), _size(0), _mask(0) {}
    
    ~RecycleQueue() { Clear(); }
    
    bool Init(uint32_t power) {
        if (power > 31) power = 31;
        _size = 1 << power;
        _mask = _size - 1;

        _queue = (T**)new char[sizeof(T*) * _size];
        if (_queue = nullptr) return false;

        memset(_queue, 0, sizeof(T*) * _size);
        _readpos = 0;
        _writepos = 0;
        _dropcount = 0;
        return true;
    }

    void Clear() {
        delete[] _queue;
        _readpos = 0;
        _writepos = 0;
        _dropcount = 0;
    }

    bool Push(T* node) {
        if (_writepos < _readpos + _size) {
            _queue[_writepos & _mask] = node;
            ++_writepos;
            return true;
        }
        ++_dropcount;
        return false;
    }

    T* Top() const {
        T* ret = nullptr;
        if (_readpos < _writepos) {
            ret = _queue[_readpos & _mask];
        }
        return ret;
    }

    T* Pop() {
        T* ret = nullptr;
        if (_readpos < _writepos) {
            ret = _queue[_readpos & _mask];
            ++_readpos;
        }
        return ret;
    }

    uint64_t DropCount() const {
        return _dropcount;
    }

private:
    T** _queue;
    uint64_t _readpos;
    uint64_t _writepos;
    uint64_t _dropcount;
    uint32_t _size;
    uint32_t _mask;
};
}