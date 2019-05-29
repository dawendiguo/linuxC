/*
 * in the process,can't catch SIGUSR1 in some other code
 * this is a bug , we do't want occur
 * so sigsuspend is for this bug
 */

#include <signal.h>
#include "ourhdr.h"

static void sig_usr1(int);

int main(void){

        sigset_t newmask,oldmask;

        if(signal(SIGUSR1,sig_usr1) == SIG_ERR)
                err_sys("signal(SIGUSR1) error");
        sigemptyset(&newmask);
        sigaddset(&newmask,SIGUSR1);

        /* block SIGUSR1 */
        if(sigprocmask(SIG_BLOCK,&newmask,&oldmask) < 0)
                err_sys("sigprocmask error");
        pr_mask("after block SIG_USR1: ");
        /*code for not catch SIGUSR1 */

        /* unblock SIG_USR1,first method:use SIG_UNBLOCK. seconde method: use SIG_SETMASK */
        if(sigprocmask(SIG_SETMASK,&oldmask,NULL) < 0)
                err_sys("SIG_SETMASK error");
        pr_mask("unblock SIG_USR1: ");
        alarm(25);
         //some other code
        pause();      //wait for signal to occur 
        exit(0);
}
static void sig_usr1(int signo){
        pr_mask("in code sig_usr1: ");
        return;
}
