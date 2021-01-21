#include <basic/common.h>
#include <basic/hittable.h>
#include <basic/camera.h>
#include <semaphore.h>
#include <pthread.h>
#include <queue>
#include <iomanip>

class thread_pool {
    public:
        struct task {
            int x, y, depth, image_height, image_width, sample_per_pixel;
            shared_ptr<hittable> world;
            shared_ptr<hittable> lights;
            shared_ptr<color[]> shaded;
            shared_ptr<camera> cam;
            color background;
        };

    private:
        int thread_num, task_num;
        sem_t task_count;
        sem_t remaining_task;
        sem_t worker_start;
        sem_t mutex_write_result;
        sem_t task_num_limit;
        sem_t mutex_q;
        std::queue<task*> q;

        static void* worker_function(void *);

        std::vector<pthread_t> pool;

        bool already_joined;
    
    public:
        thread_pool(int thread_num, int task_num_limit=1600*100);

        ~thread_pool();

        void push_task(task* new_task);

        void join(int batch_size);

        void start();
};