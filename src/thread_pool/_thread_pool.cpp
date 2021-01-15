#include <thread_pool.h>

thread_pool::thread_pool(int size) : terminate(false) {
    idle_number = size < 1 ? 1 : size;
    for(int i = 0; i < size; i++) {
        pool.emplace_back(
            [this]{
                while(!this->terminate) {
                    std::function<void()> task;
                    std::unique_lock<std::mutex> lock{this->m_lock};
                    this->cv.wait(lock,
                        [this]{
                            return this->terminate.load() || !this->tasks.empty();
                        }
                    );
                    if(this->terminate && this->tasks.empty()) return;
                    task = std::move(this->tasks.front());
                    this-> tasks.pop();

                    idle_number--;
                    task();
                    idle_number++;
                }
            }
        );
    }
}

thread_pool::~thread_pool() {
    terminate.store(true);
    cv.notify_all();
    for(auto &thread : pool) {
        if(thread.joinable())
            thread.join();
    }
}

int thread_pool::idle_count() {
    return idle_number;
}

void thread_pool::join() {
    terminate.store(true);
    cv.notify_all();
    for(auto &thread : pool) {
        if(thread.joinable())
            thread.join();
    }
}