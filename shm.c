#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = shm_open("/shm1", O_CREAT | O_RDWR, 0666);
    ftruncate(fd, 100);

    char *ptr = mmap(0, 100, PROT_WRITE, MAP_SHARED, fd, 0);
    sprintf(ptr, "Hello Shared Memory");

    return 0;
}
