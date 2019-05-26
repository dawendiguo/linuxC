/*
 * sleep2 解决了sleep1 alarm()和pause()的竞态问题
 * 不会出现alarm()到时了还没有执行到pause()，而使得系统一直挂起的情况。
 * 但又引入一个新的问题
 * 当调用sleep2函数的进程捕捉另外一个信号，而且处理另外信号的时间比设定的sleep2()--休眠时间长时，另外一个信号处理就不能顺利完成。
 * 实例名为useSleep2.c
 */
#include <setjmp.h>
#include <signal.h>
#include "ourhdr.h"

static jmp_buf env_alrm;

static void
sig_alrm(int signo){
        longjmp(env_alrm,1);
}

unsigned int
sleep2(unsigned nsecs){
        if(signal(SIGALRM,sig_alrm) == SIG_ERR)
                err_sys("SIGALRM error\n");
        //init jmp point
        if(setjmp(env_alrm) == 0){
            alarm(nsecs);
            pause();
        }
        return(alarm(0));
}
