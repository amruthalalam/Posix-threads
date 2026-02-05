#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include<string.h>

int main() {
    const char *queue = "/qu6";
    mqd_t mqd;
    //struct mq_attr attr;
    mqd = mq_open(queue, O_RDONLY );//O_NONBLOCK);
    char buffer[1024];
    int count=0;
    while (1) {
        memset(buffer,0,sizeof(buffer));
        ssize_t n = mq_receive(mqd, buffer, sizeof(buffer), NULL);
        //mq_receive(mqd, buffer, sizeof(buffer));
        if (n >= 0) {
            buffer[n] = '\0';
            printf("Received: %s\n", buffer);
        }
        // else {
        //     if (errno == EAGAIN) {
        //         printf("Polling... queue empty\n");
        //     } else {
        //         perror("mq_receive");
        //         break;
        //     }
        // }
        usleep(20000);
    }
    mq_close(mqd);
    return 0;
}