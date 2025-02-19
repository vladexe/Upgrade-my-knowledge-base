    #include <stdio.h>
    #include <unistd.h>
    #include <signal.h>
    #include <sys/wait.h>

    int main(void){

        int fork_id = 0;
        
        fork_id = fork();

        if(fork_id == -1){
            perror("fork error");
            return 1;
        }
        if(fork_id == 0){ // Child process
            while(1){
                puts("We are in child process");
                sleep(1);
            }
        } else{ // Parent process
            puts("We are in parrent process");
            sleep(3);
            // Sending pause signal to the child process
            if(kill(fork_id, SIGSTOP) == -1){
                perror("SIGSTOP error");
                return 1;
            }
            sleep(1);
            // Sending continue signal to the child process
            if(kill(fork_id, SIGCONT) == -1){
                perror("SIGCONT error");
                return 2;
            }
            sleep(3);
            // Sending termination signal to the child process
            if(kill(fork_id, SIGTERM) == -1){
                perror("SIGTERM error");
                return 3;
            }
            wait(NULL);
        }
        return(0);
    }