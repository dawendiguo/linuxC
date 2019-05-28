#include <signal.h>
#include "ourhdr.h"

Sigfunc *
my_signal(int signo,Sigfunc *func){
        struct sigaction act,oact;

        act.sa_handler = fun;
        sigemptyset(&act.sa_mask);
        act.sa_flags = 0;

        //SIGALRM not restart 
        if(signo == SIGALRM){
#ifdef  SA_INTERRUPT
                act.sa_flags |= SA_INTERRUPT;
#endif
        }
        //other's auto restart
        else{
#ifdef SA_RESTART
                act.sa_flags |= SA_RESTART;
#endif
        }

        if(sigaction(signo,&act,&oact) < 0)
                err_sys("sigaction error");
        return (oact.sa_handler);
}
