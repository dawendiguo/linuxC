/*
 * 第一个版本的sleep
 * 3个bug
 * first:调用这个sleep1的函数不能使用alarm函数，否则之前的alarm不会起作用。
 * seconde:修改了SIGALRM信号处理方式，如果之前有关于这个信号的处理就无效了。
 * third:alarm和pause有竞态关系，系统环境特别卡完全有可能alarm信号在pause运行之前发出，程序就容易被一直挂起。
 */
#include <signal.h>
#include "ourhdr.h"
#include <unistd.h>

static void sig_alrm(int signo){
        return ;
}


unsigned int 
sleep1(unsigned int nsecs){
        if(signal(SIGALRM,sig_alrm) == SIG_ERR)
                return(nsecs);
        alarm(nsecs);
        pause();
        return(alarm(0));
}
