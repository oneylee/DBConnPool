#include <iostream>
#include <memory>

template<typename T, typename... Ts>
std::unique_ptr<T> make_unique(Ts&& ...params) {
    return std::unique_ptr<T>(new T(std::forward<Ts>(params)...));
}

int main()
{
    std::unique_ptr<int> sp = make_unique<int>(123);

    return 0;
}