#include <signal.h>
#include "ourhdr.h"

Sigfunc *
signal_intr(int signo,Sigfunc *func){
        struct sigaction act,oact;

        act.sa_handler = func;
        sigemptyset(&act.sa_mask);
        act.sa_flags = 0;
        //not restart 
#ifdef SA_INTERRUPT
        act.sa_flags |= SA_INTERRUPT;
#endif
        if(sigaction(signo,&act,&oact) < 0)
                err_sys("sigaction error");
        return(oact.sa_handler);
}
