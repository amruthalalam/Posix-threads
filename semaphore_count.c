#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem1, sem2;   // Semaphores for t1 and t2
int counter = 1;

void* t1(void* arg) {
    while (counter <= 100) {
        sem_wait(&sem1); // Wait until it's t1's turn

        printf("t1: %d\n", counter++);
        
        sem_post(&sem2); // Signal t2 to proceed
    }
    return NULL;
}

void* t2(void* arg) {
    while (counter <= 100) {
        sem_wait(&sem2); // Wait until it's t2's turn

        printf("t2: %d\n", counter++);
        
        sem_post(&sem1); // Signal t1 to proceed
    }
    return NULL;
}

int main() {
    pthread_t th1, th2;

    // Initialize semaphores
    sem_init(&sem1, 0, 1);  // sem1 starts as 1, allowing t1 to go first
    sem_init(&sem2, 0, 0);  // sem2 starts as 0, blocking t2 until t1 goes

    // Create threads
    pthread_create(&th1, NULL, t1, NULL);
    pthread_create(&th2, NULL, t2, NULL);

    // Join threads
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    // Destroy semaphores
    sem_destroy(&sem1);
    sem_destroy(&sem2);

    return 0;
}
