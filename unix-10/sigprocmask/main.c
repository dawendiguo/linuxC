#include <signal.h>
#include "ourhdr.h"

static void sig_quit(int);

int
main(void){
        sigset_t newmask,oldmask,pendmask;

        if(signal(SIGQUIT,sig_quit) == SIG_ERR)
                err_sys("signal(SIGQUIT) error");
        sigemptyset(&newmask);
        sigaddset(&newmask,SIGQUIT);

        if(sigprocmask(SIG_BLOCK,&newmask,&oldmask) < 0)
                err_sys("SIG_BLOCK error");
        sleep(5);

        if(sigpending(&pendmask) < 0)
                err_sys("sigpending error");
        if(sigismember(&pendmask,SIGQUIT))
                printf("\n SIGQUIT pending\n");
        if(sigismember(&pendmask,SIGUSR1))
                printf("\n SIGUSR1 pending\n");
        else
                printf("\n SIGUSR1 not pending\n");

        /* unblock SIGQUIT */
        if(sigprocmask(SIG_UNBLOCK,&newmask,&oldmask) < 0)
                err_sys("SIG_UNBLOCK error");
        if(sigpending(&pendmask) < 0)
                err_sys("sigpending error");

        if(sigismember(&pendmask,SIGQUIT))
                printf("SIGQUIT pending\n");
        else
                printf("SIGQUIT not pending\n");
        printf("SIGQUIT unblocked\n");

        sleep(5);
        exit(0);
}

static void sig_quit(int signo){
        printf("caught SIGQUIT\n");

        if(signal(SIGQUIT,SIG_DFL) == SIG_ERR)
                err_sys("can't reset SIGQUIT\n");
        return;
}
