#include "ourhdr.h"
#include <signal.h>

static void sig_pipe(int);      /* our signal handler */

int
main(void){
        int n,fd[2];
        pid_t pid;
        char line[MAXLINE];

        if(signal(SIGPIPE,sig_pipe) == SIG_ERR)
                err_sys("signal error");

        if(s_pipe(fd) < 0)
                err_sys("pipe error");

        if( (pid = fork()) < 0)
                err_sys("fork error");
        else if(pid > 0){                       /* parent */
                close(fd[0]);
                while(fgets(line,MAXLINE,stdin) != NULL){
                        n = strlen(line);
                        if(write(fd[1],line,n) != n)
                                err_sys("write error");
                        if( ( n = read(fd[1],line,MAXLINE)) != n) 
                                err_sys("read from pipe");
                        if( n == 0){
                                err_msg("child closed pipe");
                                break;
                        }
                        line[n] = 0;
                        if(fputs(line,stdout) == EOF)
                                err_sys("fputs error");
                }
                if(ferror(stdin))
                        err_sys("fgets error on stdin");
                exit(0);
                }
        else{             /* child */
                close(fd[1]);
                if(fd[0] != STDIN_FILENO){
                        if(dup2(fd[0],STDIN_FILENO) != STDIN_FILENO)
                                err_sys("dup2 error to stdin");
                }
                if(fd[0] != STDOUT_FILENO){
                        if(dup2(fd[0],STDOUT_FILENO) != STDOUT_FILENO){
                                err_sys("dup2 error to stdout");
                        }
                }
                if(execl("./add","add",NULL) < 0)
                        err_sys("execl error");
        }
}
static void 
sig_pipe(int signo){
        printf("SIGPIPE caught\n");
        exit(1);
}
