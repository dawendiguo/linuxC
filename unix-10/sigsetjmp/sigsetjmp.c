/*
 * 用sigsetjmp处理signal函数，可以将当前处理的信号加入屏蔽字。
 * longjmp返回时再恢复。
 */

#include <signal.h>
#include <setjmp.h>
#include <time.h>
#include "ourhdr.h"

static void sig_usr1(int),sig_alrm(int);
static sigjmp_buf jmpbuf;
//用这个位保存sigsetjmp的初始化状态，初始化完成后canjump为非0，表示可以使用longjmp返回，否则不能使用longjmp.
//sig_atomic_t 是不会被中断的变量类型，可以用一条机器指令对其进行存取，这种类型数据总是被定义为volatile
static volatile sig_atomic_t canjump;

int
main(void){
          if(signal(SIGUSR1,sig_usr1) == SIG_ERR)
                  err_sys("signal(SIGUSR1) error");
          if(signal(SIGALRM,sig_alrm) == SIG_ERR)
                  err_sys("signal(SIGALRM) error");

          /*print current sigprocmask*/
          pr_mask("starting main: ");
          /*return from siglongjmp*/
          if(sigsetjmp(jmpbuf,1)){
                  pr_mask("ending main: ");
                  exit(0);
          }
          /* set canjump not zero */
          canjump = 1;

          for(;;)
                  pause();
}

static void 
sig_usr1(int signo){
        time_t starttime;

        /* sigsetjmp not init */
        if(canjump == 0)
                return ;

        pr_mask("starting sig_usr1: ");
        alarm(3);

        starttime = time(NULL);
        for(;;)
                if(time(NULL) > starttime + 5)
                        break;
        pr_mask("finishing sig_usr1：");
        //can not jump 
        canjump = 0;
        siglongjmp(jmpbuf,1);    //jump to sigsetjmp
}

static void 
sig_alrm(int signo){
        pr_mask("in sig_alrm: ");
        return;
}
