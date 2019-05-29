/*
 * sigsuspend() unblock a signal + pause();
 * after sigsuspend() , mask restore before
 */
#include <signal.h>
#include "ourhdr.h"

static void sig_int(int);
int 
main(void){
        sigset_t newmask,oldmask,zeromask;

        //catch SIGINT
        if(signal(SIGINT,sig_int) == SIG_ERR)
                err_sys("signal(SIGINT) error");

        sigemptyset(&newmask);
        sigemptyset(&zeromask);
        sigaddset(&newmask,SIGINT);

        /* block SIGINT */
        if(sigprocmask(SIG_BLOCK,&newmask,&oldmask) < 0)
                err_sys("SIG_BLOCK error");

        pr_mask("in critical region: ");

        /* unblock success and pause*/
        if(sigsuspend(&zeromask) != -1)
                err_sys("sigsuspend error");
        pr_mask("after return from sigsuspend: ");

        //reset sigmask
        if(sigprocmask(SIG_SETMASK,&oldmask,NULL) < 0)
                err_sys("SIG_SETMASK error");
        pr_mask("after SIG_SETMASK : ");
        exit(0);
}

static void sig_int(int signo){
        pr_mask("\n in sig_int: ");
        return;
}
