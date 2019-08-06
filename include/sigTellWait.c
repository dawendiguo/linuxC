#include "ourhdr.h"
/* signal implement TELL_WAIT,TELL_PARENT,TELL_CHILD,WAIT_PARENT,WAIT_CHILD
 */

/* child or parent is done , set this flag */
static volatile sig_atomic_t sigflag;
static sigset_t newmask,oldmask,zeromask;

static void sig_usr(int signo){
        sigflag = 1;
        return;
}

/* block SIGUSR1 SIGUSR2 */
void TELL_WAIT(void){
        if(signal(SIGUSR1,sig_usr) == SIG_ERR)
                err_sys("signal(SIGUSR1) error");
        if(signal(SIGUSR2,sig_usr) == SIG_ERR)
                err_sys("signal(SIGUSR2) error");

        sigemptyset(&zeromask);

        sigemptyset(&newmask);
        sigaddset(&newmask,SIGUSR1);
        sigaddset(&newmask,SIGUSR2);

        /*block SIGUSR1 and SIGUSR2, and save current signal mask */
        if(sigprocmask(SIG_BLOCK,&newmask,&oldmask) < 0)
                err_sys("SIG_BLOCK error");

}

/* TELL PARENT , child is done */
void TELL_PARENT(pid_t pid){
        kill(pid,SIGUSR2);
}

/* WAIT PARENT , pause childe util parent done */
void WAIT_PARENT(void){
        //sigflag == 0 ,parent is running
        while(sigflag == 0)
                //wait for parent sent SIGUSR1
                sigsuspend(&zeromask);
        /* reset sigflag to 0*/
        sigflag = 0;

        //reset signal mask to original value */
        if(sigprocmask(SIG_SETMASK,&oldmask,NULL) < 0)
                err_sys("SIG_SETMASK error");
}

/* TELL CHILE , parent is done */
void TELL_CHILD(pid){
        kill(pid,SIGUSR1);
}

/* WAIT CHILD , pause parent util child sent SIGUSR2 */
void WAIT_CHILD(void){
        //child is not done
        while(sigflag == 0)
                sigsuspend(&zeromask);
        /* reset sigflag to 0 */
        sigflag = 0;
        /* reset signal mask to original value */
        if(sigprocmask(SIG_SETMASK,&oldmask,NULL) < 0)
                err_sys("SIG_SETMASK error");
}
