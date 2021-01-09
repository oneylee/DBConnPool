#pragma once
#include <mutex>
#include <memory>
#include "macros.h"

namespace orz
{
template<typename T>
class Singleton
{
public:
    
    static T* GetInstance() {
        std::once_flag flag;
        std::call_once(flag, [&] () { _singleton.reset(new T()); });
        return _singleton.get();
    }
private:
    Singleton() {}
    ~Singleton() {}
    DISALLOW_COPY_AND_ASSIGN(Singleton);
    static std::shared_ptr<T> _singleton;
};

template<typename T>
T* Singleton<T>::_singleton = nullptr;
}