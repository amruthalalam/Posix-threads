#include <stdio.h>
#include <pthread.h>
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int data = 0;
int available = 0;
void* producer(void* arg) {
    pthread_mutex_lock(&mutex);
    data = 100;
    available = 1;
    printf("Producer produced data\n");
    pthread_cond_signal(&cond);  
    pthread_mutex_unlock(&mutex);
    return NULL;
}
void* consumer(void* arg) {
    pthread_mutex_lock(&mutex);
    while (available == 0)       
        pthread_cond_wait(&cond, &mutex);
    printf("Consumer consumed data: %d\n", data);
    pthread_mutex_unlock(&mutex);
    return NULL;
}
int main() {
    pthread_t p, c;
    pthread_create(&c, NULL, consumer, NULL);
    pthread_create(&p, NULL, producer, NULL);
    pthread_join(p, NULL);
    pthread_join(c, NULL);
    return 0;
}

