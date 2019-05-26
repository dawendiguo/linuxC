/*
 * 第一个只能用exit()设定timeout时间，
 * 而这里使用的setjmp和longjmp的方法为read设定超时时间。
 */
#include <setjmp.h>
#include <signal.h>
#include "ourhdr.h"

static void my_alarm(int);
static jmp_buf env_jmp;

int
main(void){
        int n;
        int line[MAXLINE];

        if(signal(SIGALRM,my_alarm) == SIG_ERR)
                err_sys("signal(SIGALRM) error\n");
        //jump from longjmp or init env_jmp error
        if(setjmp(env_jmp) != 0)
                err_quit("read time out\n");
        //set timeout times
        alarm(10);
        if( (n = read(STDIN_FILENO,line,MAXLINE)) < 0)
                err_sys("read string error\n");
        //delete alarm
        alarm(0);
        
        //printf getting string
        write(STDOUT_FILENO,line,MAXLINE);
        exit(0);
}

static void my_alarm(int signo){
        longjmp(env_jmp,1);
}
