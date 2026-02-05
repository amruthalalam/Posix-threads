// start count c1 from 0 to 20, if c1 is 10 start count c4 form 0 to 5 ,
// if c4 is 5 , reset c4 = 0 and start count c3 from 0 to 5, if c1 is 20 ,
//  count c2++, and reset c1, c3, c4 count
 
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
 
pthread_t thread1;
pthread_t thread2;
pthread_t thread3;
pthread_t thread4;
 
   pthread_mutex_t mutex  =   PTHREAD_MUTEX_INITIALIZER;
// pthread_mutex_t mutex2  =  PTHREAD_MUTEX_INITIALIZER;
// pthread_mutex_t mutex3  =  PTHREAD_MUTEX_INITIALIZER;
   pthread_mutex_t mutex4  =  PTHREAD_MUTEX_INITIALIZER;
 
int c1 = 0;
int c2 = 0;
int c3 = 0;
int c4 = 0;
 
int iret1, iret2, iret3, iret4;

void* count1(void *arg);
void* count2(void *arg);
void* count3(void *arg);
void* count4(void *arg); 
 
void* count1(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        if (c1 <= 20) {
            c1++;
        printf("    c1 = %d  \n ", c1);
         //printf("c1 = %d ", c1);
         if(c2 == 5){
                    pthread_cancel(thread4);
                }
            if (c1 == 11) {
               // pthread_mutex_lock(&mutex);
                pthread_create(&thread4, NULL, count4, NULL);
                // printf("\n");
                if(c2 == 5){
                    pthread_cancel(thread4);
                }
 
               // pthread_mutex_lock(&mutex);
            }
 
            if (c1 == 20) {
                c2++;
                printf("--------------------------------c2 = %d --------------------------------", c2);
                c1 = 0;
                c3 = 0;
                c4 = 0;
                printf("\n");
 
                printf("\n");
            }
        }
        pthread_mutex_unlock(&mutex);
        sleep(0.1);
    }
    return NULL;
}
 
void* count4(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        if (c4 <= 5) {
            c4++;
            printf("    c4 = %d \n ", c4);
 
            if (c4 == 5) {
                c4 = 0;
                pthread_create(&thread3, NULL, count3, NULL);
                // printf("\n");
            }
        }
        if(c2 == 5){
                    pthread_cancel(thread4);
                }
        pthread_mutex_unlock(&mutex);
        sleep(0.1);
    }
    return NULL;
}
 
void* count3(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        if (c3 <= 5) {
            c3++;
            printf("    c3 = %d    \n", c3);
        }
        pthread_mutex_unlock(&mutex);
        sleep(0.1);
    }
    return NULL;
}
 
void* count2(void *arg) {
    while (1) {
        sleep(0.1);
        if(c2 == 5){
           
            // pthread_cancel(thread3);
            // pthread_cancel(thread4);
            // pthread_cancel(thread1);
            // pthread_cancel(thread2);
            exit(-1);
 
        }
    }
    return NULL;
}
 
int main() {
    pthread_create(&thread1, NULL, count1, NULL);
    pthread_create(&thread2, NULL, count2, NULL);
 
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);
 
   
    // pid_t pid = getpid(thread1);
    // printf("%d", )
    // if(c2 == 5){
    //     exit()
    // }
    //printf("Final counts: c1=%d, c2=%d, c3=%d, c4=%d\n", c1, c2, c3, c4);
 
    return 0;
}
 
 