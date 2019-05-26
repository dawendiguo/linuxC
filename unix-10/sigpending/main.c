#include <signal.h>
#include "ourhdr.h"
#include <sys/types.h>

static void my_user1(int);
int
main(void){
    if(signal(SIGUSR1,my_user1) == SIG_ERR)
            err_sys("signal SIGUSR1 error");
    sigpending(SIGUSR1);
    pause();
    exit(0);
}

static void my_user1(int signo){
        if(signo == SIGUSR1)
                printf("catch signo : SIGUSR1\n");
        else
                printf("catch unknow signo: %d\n",signo);
        return;
}
