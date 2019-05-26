#include "ourhdr.h"
#include <signal.h>

static void sig_usr(int);

int main(void){
        if(signal(SIGUSR1,sig_usr) == SIG_ERR)
                err_sys("can't catch SIGUSE1");
        if(signal(SIGUSR2,sig_usr) == SIG_ERR)
                err_sys("can't catch SIGUSE2");

        for(;;)
                pause();
}

static void sig_usr(int signo){
        if(signo == SIGUSR1)
                err_ret("receive sig user1\n");
        else if(signo == SIGUSR2)
                err_ret("receive sig user2\n");
        else
                err_dump("received signal %d \n",signo);
        return ;
}
