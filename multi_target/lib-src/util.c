#include <pthread.h>

#include "util.h"

tid_t thread_start (thread_worker_t worker, void *args)
{
    tid_t tid = -1;
    pthread_attr_t attr;

    /* init thread attributes */
    pthread_attr_init(&attr);

    pthread_create(&tid, &attr, worker, args);
    return tid;
}
