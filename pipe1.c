#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int fd1[2], fd2[2];
    pipe(fd1); // parent → child
    pipe(fd2); // child → parent

    if (fork() == 0) {
        // CHILD (t2)
        int counter;
        while (1) {
            read(fd1[0], &counter, sizeof(counter));
            if (counter > 100) break;

            printf("t2: %d\n", counter++);
            write(fd2[1], &counter, sizeof(counter));
        }
    } else {
        // PARENT (t1)
        int counter = 1;
        while (counter <= 100) {
            printf("t1: %d\n", counter++);
            write(fd1[1], &counter, sizeof(counter));
            read(fd2[0], &counter, sizeof(counter));
        }
        wait(NULL);
    }
    return 0;
}
