/*
 * 为read设置超时停止
 * 但有2个bug
 * 1.alarm()和read()有竞态关系，有可能alarm()时间到了而read()还没有执行。使系统一直执行read()
 * 2.read()如果系统支持再起动，read()不会被终止，alarm()不会起作用
 */

#include <signal.h>
#include "ourhdr.h"

static void sig_alarm(int);

int
main(void){
        int n;
        char line[MAXLINE];

        if(signal(SIGALRM,sig_alarm) == SIG_ERR)
                err_sys("signal(SIGALRM) error\n");
        alarm(5);
        if( (n = read(STDIN_FILENO,line,MAXLINE)) < 0)
                err_sys("read error\n");
        alarm(0);

        write(STDOUT_FILENO,line,n);
        exit(0);
}

static void sig_alarm(int signo){
        printf("read time out\n");
        exit(2);
}
