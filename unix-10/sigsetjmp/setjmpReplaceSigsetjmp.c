#include <signal.h>
#include <setjmp.h>
#include <time.h>
#include "ourhdr.h"

static void sig_usr1(int),sig_alrm(int);
static jmp_buf jmpbuf;
static volatile sig_atomic_t canjump;

int main(void){
        if(signal(SIGUSR1,sig_usr1) == SIG_ERR)
                err_sys("signal(SIGUSR1) error");
        if(signal(SIGALRM,sig_alrm) == SIG_ERR)
                err_sys("signal(SIGALRM) error");

        pr_mask("starting main: ");
        if(setjmp(&jmpbuf) != 0){
                pr_mask("ending main: ");
                exit(0);
        }

        canjump = 1;
        for(;;)
                pause();
}

static void sig_usr1(int signo){
        time_t starttime;

        if(canjump == 0)
                return;

        pr_mask("starting sig_usr1: ");

        alarm(3);
        
        starttime = time(NULL);

        for(;;)
                if(time(NULL) > starttime + 5)
                        break;

        pr_mask("finishing sig_usr1: ");
        longjmp(&jmpbuf,1);
}

static void sig_alrm(int signo){
        pr_mask("in sig_alrm: ");
        return;
}
