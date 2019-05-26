#include <signal.h>
#include "ourhdr.h"

static void my_usr1(int);
int
main(void){
        if(signal(SIGUSR1,my_usr1) == SIG_ERR)
                err_sys("signal error for SIGUSR1\n");
        printf("before alarm\n");
        alarm(100);
        pause();
        printf("after alarm and pause \n");
        exit(alarm(0));
}

static void my_usr1(int signo){
        printf("own sig Function\n");
}
