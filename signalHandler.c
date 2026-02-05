#include <stdio.h>
#include <signal.h>
#include <unistd.h>
void handler(int sig) {
    if (sig == SIGINT)
        printf("Caught SIGINT (Ctrl+C). Not terminating.\n");
    else if (sig == SIGQUIT)
        printf("Caught SIGQUIT (Ctrl+\\). Not terminating.\n");
    else if (sig == SIGTERM)
        printf("Caught SIGTERM. Not terminating.\n");
}
int main() {
    signal(SIGINT, handler);    // Ctrl+C
    signal(SIGQUIT, handler);   // Ctrl+
    signal(SIGTERM, handler);   // kill <pid>

    printf("Process running. Try Ctrl+C, Ctrl+\\, kill <pid>\n");
    while (1) {
        pause(); 
    }
    return 0;
}
