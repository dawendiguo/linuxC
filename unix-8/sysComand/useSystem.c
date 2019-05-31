#include <sys/types.h>
#include <signal.h>
#include "my_system.c"
#include "ourhdr.h"

static void sig_int(int),sig_chld(int);

int
main(void){

        int status;

        if(signal(SIGINT,sig_int) < 0)
                err_sys("signal(SIGINT) error");
        if(signal(SIGCHLD,sig_chld) < 0)
                err_sys("signal(SIGCHLD) error");

        if((status = my_system("/bin/ed")) < 0)
                err_sys("system() error");
        exit(0);
}

static void sig_int(int signo){
        printf("caught SIGINT\n");
        return;
}

static void sig_chld(int signo){
        printf("caught SIGCHLD\n");
        return;
}
