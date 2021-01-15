#pragma once

#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <functional>
#include <condition_variable>
#include <atomic>
#include <future>

class thread_pool {
    using Task = std::function<void()>;
    private:
        std::vector<std::thread> pool;
        std::queue<Task> tasks;
        std::mutex m_lock;
        std::condition_variable cv;
        std::atomic<bool> terminate;
        std::atomic<int> idle_number;
        
    public:
        thread_pool(int size);
        ~thread_pool();

        template<class F, class... Args>
        auto commit(F&& f, Args&&... args) -> std::future<decltype(f(args...))> {
            if(terminate.load()) throw std::runtime_error("commit after thread pool has terminated.");

            using ret_type = decltype(f(args...));
            auto task = std::make_shared<std::packaged_task<ret_type()>>(
                std::bind(std::forward<F>(f), std::forward<Args>(args)...)
            );

            std::future<ret_type> future = task->get_future();
            std::lock_guard<std::mutex> lock{m_lock};
            tasks.emplace(
                [task](){
                    (*task)();
                }
            );
            cv.notify_one();
            return future;
        }
        int idle_count();
        void join();
};