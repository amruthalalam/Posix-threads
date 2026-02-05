#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
int main() 
{
    const char *queue = "/qu5";
    mqd_t mqd;
    struct mq_attr attr;
    attr.mq_curmsgs=0;
    attr.mq_flags=0;
    attr.mq_maxmsg=10;
    attr.mq_msgsize=1024;
    mqd = mq_open(queue, O_CREAT | O_WRONLY, 0666, &attr);
    // if(mqd==(mqd_t)-1)
    // {
    //     perror("mq_open");
    //     return 1;
    // }
    char buffer[1024]="hello";

    while (1) {
        if(mq_send(mqd, buffer, strlen(buffer), 0)==-1)
        {
            perror("mq_send");
            break;
        }
        printf("Sent: %s\n", buffer);
        sleep(4);
    }
    
    mq_close(mqd);
    mq_unlink("/qu5");
    return 0;
}
