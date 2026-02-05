#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <unistd.h>

typedef struct {
    int counter;
    int turn;
} shm_data;

int main() {
    int fd = shm_open("/turn_shm", O_CREAT | O_RDWR, 0666);
    ftruncate(fd, sizeof(shm_data));

    shm_data *data = mmap(NULL, sizeof(shm_data),
                          PROT_READ | PROT_WRITE,
                          MAP_SHARED, fd, 0);

    sem_t *sem = sem_open("/turn_sem", O_CREAT, 0666, 1);

    if (fork() == 0) {
        // t2
        while (1) {
            sem_wait(sem);
            if (data->counter > 100) {
                sem_post(sem);
                break;
            }
            if (data->turn == 2) {
                printf("t2: %d\n", data->counter++);
                data->turn = 1;
            }
            sem_post(sem);
        }
    } else {
        // t1
        data->counter = 1;
        data->turn = 1;

        while (1) {
            sem_wait(sem);
            if (data->counter > 100) {
                sem_post(sem);
                break;
            }
            if (data->turn == 1) {
                printf("t1: %d\n", data->counter++);
                data->turn = 2;
            }
            sem_post(sem);
        }

        shm_unlink("/turn_shm");
        sem_unlink("/turn_sem");
    }
    return 0;
}
