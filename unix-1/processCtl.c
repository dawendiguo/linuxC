#include <sys/types.h>
#include <sys/wait.h>
#include "ourhdr.h"

int main(void){
    char buf[MAXLINE];
    pid_t pid;
    int status;

    printf("%% ");          //print prompt %% fro display %
    while(fgets(buf,MAXLINE,stdin) != NULL){
        buf[strlen(buf) -1 ] = 0;           //replace newline with null

        if((pid = fork()) < 0){ 
            err_sys("fork error");
        }
        //child proces
        else if(pid == 0){
            execlp(buf,buf,(char *) 0);
            err_ret("couldn't execute: %s",buf);
            exit(127);
        }
        //parent process
        if( (pid = waitpid(pid,&status,0)) < 0){
            err_sys("waitpid error");
        }
        printf(" %%");
    }
    exit(0);
}
