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
        static std::once_flag flag;
        std::call_once(flag, [&]() { _singleton.reset(new T()); });
        // _singleton.reset(new T());
        return _singleton.get();
    }
protected:
    Singleton() {}
    ~Singleton() {}
    static std::shared_ptr<T> _singleton;
private:
    DISALLOW_COPY_AND_ASSIGN(Singleton);
    
};

template<typename T>
std::shared_ptr<T> Singleton<T>::_singleton;
}