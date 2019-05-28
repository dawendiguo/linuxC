#include <signal.h>
#include <errno.h>

#define SIGBAD(signo) ((signo) <= 0 || (signo) >= NSIG)
    /*<signal.h> usually defines NSIG to include signal numer 0 */

int sigaddset(sigset_t *set,int signo){
        if(SIGBAD(signo)){
                errno = EINVAL;
                return(-1);
        }
        //open sigset_t signo bit,no signo equals 0,so signo - 1;
        *set |= 1<<(signo-1);
        return(0);
}

int sigdelset(sigset_t *set,int signo){
        if(SIGBAD(signo)){
                errno = EINVAL;
                return(-1);
        }
        //close sigset_t signo bit
        *set &= ~(1<<(signo-1));
        return(0);
}

int sigismember(const sigset_t *set,int signo){
        if(SIGBAD(signo)){
                errno = EINVAL;
                return(-1);
        }
        return( (*set & (1<<(signo - 1))) != 0);
}
