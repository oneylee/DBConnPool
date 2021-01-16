
#include <iostream>

#include "threadpool.h"

int main()
{
    orz::ThreadPool pool(5);
    std::vector<std::future<size_t>> results;

    auto tt = [] (size_t i){
        std::cout << "hello " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "world " << i << std::endl;
        return i * i;
    };
    for (size_t i = 0; i < 10; ++i) {
        results.emplace_back(
        pool.Enqueue(
            tt, i
        ));
    }

    for (auto& result : results) {
        std::cout << result.get() << ' ';
    }
    std::cout << std::endl;
    return 0;

}