#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>

void handler(int signum) {
    printf("Received signal %d:\n", signum);

    static int counter = 0;
    if(signum == SIGALRM){
        puts("SIGALRM IS RECIVED");
        puts("Counter is 0 now");
        counter = 0;
    }
    if(signum == SIGTSTP){
        puts("CTRL+Z SIGTSTP IS RECIVED");
        puts("Process will be not stoped");
    }
    if(signum == SIGINT){
        counter += 1;
        alarm(3);
        puts("SIGINT signal recived. Please enter two more time within 3 second to exit");
        if(counter == 3){
            exit(0);
        }
    }
    if(signum == SIGCONT){
        puts("SIGCONT IS RECIVED");  
    }
    if(signum == SIGTERM){
        puts("SIGTERM IS RECIVED");
        puts("Exiting...");
        exit(0);
    }
}

int main(void) {
    struct sigaction sa;
    sa.sa_handler = handler;
    sa.sa_flags = 0;  

    sigaction(SIGTSTP, &sa, NULL); 
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGALRM, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);

    printf("PID: %d\n", getpid());
    
    while (1) {
        puts("Running...");
        sleep(1);
    }
    return 0;
}
