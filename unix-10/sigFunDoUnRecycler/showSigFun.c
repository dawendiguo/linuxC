#include <sys/types.h>
#include <signal.h>
#include "ourhdr.h"

static void my_alarm(int);

int
main(void){
        if( (signal(SIGALRM,my_alarm)) == SIG_ERR)
                err_sys("signal error for SIGALRM");

        alarm(1);
        pause();

        printf("main is over!\n");
        exit(0);
}

static void my_alarm(int signo){
        printf("custom alarm handler my_alarm() running\n");
        return;
}

