#include <thread_pool.h>

thread_pool::thread_pool(int thread_num, color(*color_function)(const ray&, const hittable&, int)) : thread_num(thread_num), color_function(color_function) {
    sem_init(&task_count, 0, 0);
    sem_init(&remaining_task, 0, 0);
    sem_init(&mutex_q, 0, 1);
    task_num = 0;
    for(int i = 0; i < thread_num; i++) {
        pthread_t t;
        pthread_create(&t, NULL, worker_function, this);
        pool.push_back(t);
    }
}

thread_pool::~thread_pool() {
    join();
}

void* thread_pool::worker_function(void *arg) {
    thread_pool *pool = (thread_pool*)arg;
    while(true) {
        sem_wait(&pool->task_count);
        
        sem_wait(&pool->mutex_q);
        task t = pool->q.front();
        pool->q.pop();
        sem_post(&pool->mutex_q);

        t.shaded[t.idx] += pool->color_function(t.r, *t.world, t.depth);
        sem_post(&pool->remaining_task);
    }
}

void thread_pool::push_task(const ray &r, const shared_ptr<hittable> &world, const int depth, const int idx, const shared_ptr<color[]> &shaded) {
    sem_wait(&mutex_q);
    q.push({
        r,
        world,
        depth,
        idx,
        shaded
    });
    sem_post(&mutex_q);

    sem_post(&task_count);
    task_num++;
}

void thread_pool::join() {
    for(int i = 0; i < task_num; i++)
        sem_wait(&remaining_task);
    for(auto &thread : pool) {
        pthread_cancel(thread);
    }
}