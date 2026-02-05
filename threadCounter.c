#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int counter = 1;
int turn = 1; // 1 -> t1, 2 -> t2

void* t1(void* arg) {
    while (counter <= 100) {
        pthread_mutex_lock(&mutex);
        while (turn != 1)
            pthread_cond_wait(&cond, &mutex);

        printf("t1: %d\n", counter++);
        turn = 2;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void* t2(void* arg) {
    while (counter <= 100) {
        pthread_mutex_lock(&mutex);
        while (turn != 2)
            pthread_cond_wait(&cond, &mutex);

        printf("t2: %d\n", counter++);
        turn = 1;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t th1, th2;
    pthread_create(&th1, NULL, t1, NULL);
    pthread_create(&th2, NULL, t2, NULL);

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    return 0;
}