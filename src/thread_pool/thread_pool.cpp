#include <thread_pool.h>

thread_pool::thread_pool(int thread_num, int task_num_limit) : thread_num(thread_num) {
    sem_init(&task_count, 0, 0);
    sem_init(&remaining_task, 0, 0);
    sem_init(&mutex_q, 0, 1);
    sem_init(&worker_start, 0, 0);
    sem_init(&mutex_write_result, 0, 1);
    sem_init(&this->task_num_limit, 0, task_num_limit);
    task_num = 0;
    for(int i = 0; i < thread_num; i++) {
        pthread_t t;
        pthread_create(&t, NULL, worker_function, this);
        pool.push_back(t);
    }
    already_joined = false;
}

thread_pool::~thread_pool() {
    join(2e8);
}

void* thread_pool::worker_function(void *arg) {
    thread_pool *pool = (thread_pool*)arg;
    sem_wait(&pool->worker_start);
    while(true) {
        sem_wait(&pool->task_count);
        
        sem_wait(&pool->mutex_q);
        thread_pool::task *t = pool->q.front();
        pool->q.pop();
        sem_post(&pool->mutex_q);

        color shaded({0, 0, 0});
        for(int i = 0; i < t->sample_per_pixel; i++) {
            auto u = (t->x + common::random()) / (t->image_width + 1);
            auto v = (t->y + common::random()) / (t->image_height + 1);
            ray r = t->cam->get_ray(u, v);
            shaded += t->cam->color_function(r, t->background, t->world, t->lights, t->depth);
        }

        sem_wait(&pool->mutex_write_result);
        t->shaded[t->y * t->image_width + t->x] = shaded;
        sem_post(&pool->mutex_write_result);
        sem_post(&pool->remaining_task);
        sem_post(&pool->task_num_limit);
        delete t;
    }
}

void thread_pool::push_task(thread_pool::task *new_task) {
    if(already_joined) return;
    sem_wait(&task_num_limit);
    sem_wait(&mutex_q);
    q.push(new_task);
    sem_post(&mutex_q);

    sem_post(&task_count);
    task_num++;
}

void thread_pool::join(int batch_size) {
    if(already_joined) return;
    already_joined = true;
    int t = 0;
    std::cerr << "\n";
    for(int i = 0; i < task_num; i++) {
        sem_wait(&remaining_task);
        t++;
    }
    for(auto &thread : pool) {
        pthread_cancel(thread);
    }
}

void thread_pool::start() {
    for(int i = 0; i < thread_num; i++)
        sem_post(&worker_start);
}