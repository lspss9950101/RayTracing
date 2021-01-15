#include <basic/common.h>
#include <basic/hittable.h>
#include <semaphore.h>
#include <pthread.h>
#include <queue>

class thread_pool {
    private:
        int thread_num, task_num;
        sem_t task_count;
        sem_t remaining_task;

        struct task {
            ray r;
            shared_ptr<hittable> world;
            int depth;
            int idx;
            shared_ptr<color[]> shaded;
        };

        sem_t mutex_q;
        std::queue<task> q;

        static void* worker_function(void *);

        std::vector<pthread_t> pool;

        color(*color_function)(const ray&, const hittable&, int);
    
    public:
        thread_pool(int thread_num, color(*color_function)(const ray&, const hittable&, int));

        ~thread_pool();

        void push_task(const ray &r, const shared_ptr<hittable> &world, const int depth, const int idx, const shared_ptr<color[]> &shaded);

        void join();
};