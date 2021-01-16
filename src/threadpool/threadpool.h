#pragma once

#include <mutex>
#include <queue>
#include <vector>
#include <thread>
#include <future>
#include <condition_variable>

namespace orz
{
class ThreadPool
{
public:
    ThreadPool(size_t size);
    template<typename F, typename... Args> 
    auto Enqueue(F&& func, Args&&... args)
        -> std::future<typename std::result_of<F(Args...)>::type>;
    ~ThreadPool();
private:
    std::vector<std::thread> _workers;
    std::queue<std::function<void()>> _tasks;
    std::condition_variable _cond;
    std::mutex _mutex;
    bool _stop;
};

ThreadPool::ThreadPool(size_t size) : _stop(nullptr) {
    for (size_t i = 0; i < size; ++i) {
        _workers.emplace_back(
            [this] {
                while (true) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> ll(this->_mutex);
                        this->_cond.wait(ll, [this] {
                            return this->_stop || !this->_tasks.empty();
                        });

                        if (this->_stop && this->_tasks.empty()) return;

                        task = this->_tasks.front();
                        this->_tasks.pop();
                    }
                    task();
                }
            }
        );
    }
}

template<typename F, typename... Args>
auto ThreadPool::Enqueue(F&& func, Args&&... args)
    -> std::future<typename std::result_of<F(Args...)>::type> {
    using return_type = typename std::result_of<F(Args...)>::type;
    std::cout << typeid(return_type).name() << std::endl;
    auto task = std::make_shared<std::packaged_task<return_type()>>(
        std::bind(std::forward<F>(func), std::forward<Args>(args)...)
    );
    std::future<return_type> result = task->get_future();
    {
        std::unique_lock<std::mutex> ll(_mutex);
        _tasks.emplace([task] { (*task)(); });
    }
    _cond.notify_one();
    return result;
}

ThreadPool::~ThreadPool() {
    _stop = true;
    _cond.notify_all();
    for (auto& work : _workers) {
        work.join();
    }
}
}