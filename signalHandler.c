/*Input	            What it actually is	Can we handle it?
Ctrl + C	              SIGINT	                 YES
*Ctrl + * 
(often mistaken as Ctrl+Q)	SIGQUIT	                YES
Ctrl + D	            EOF, NOT a signal	No signal to catch
kill -9	                       SIGKILL	IMPOSSIBLE (cannot be caught or ignored)*/
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// Signal handler function
void handler(int sig) {
    if (sig == SIGINT)
        printf("Caught SIGINT (Ctrl+C). Not terminating.\n");
    else if (sig == SIGQUIT)
        printf("Caught SIGQUIT (Ctrl+\\). Not terminating.\n");
    else if (sig == SIGTERM)
        printf("Caught SIGTERM. Not terminating.\n");
}

int main() {
    // Register handlers
    signal(SIGINT, handler);    // Ctrl+C
    signal(SIGQUIT, handler);   // Ctrl+
    signal(SIGTERM, handler);   // kill <pid>

    printf("Process running. Try Ctrl+C, Ctrl+\\, kill <pid>\n");

    while (1) {
        pause();   // wait for signals
    }

    return 0;
}
