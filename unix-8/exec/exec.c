#include <sys/types.h>
#include "ourhdr.h"
#include <sys/wait.h>

//temp environ
char *env_init[] = { "USER = unknown", "PATH=/tmp", NULL};

int main(void){
        pid_t pid;

        if( (pid = fork()) < 0)
                err_sys("fork error");
        else if( pid == 0){
               if(execle("/home/html/linux/unix-8/exec/echoall",
                          "echoall","first","second",(char *)0,
                          env_init) < 0)
                      err_sys("execle error");
        }

        if(waitpid(pid,NULL,0) < 0)
                err_sys("waitpid error");

        if( ( pid = fork()) < 0)
                err_sys("fork error");
        else if(pid == 0){
                if(execlp("echoall",
                          "echoall","first","second","third",(char *)0) < 0)
                        err_sys("execlp error");
        }
        if(waitpid(pid,NULL,0) < 0)
                err_sys("waitpid error");
        exit(0);
}
