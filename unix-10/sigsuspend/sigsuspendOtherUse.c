#include <signal.h>
#include "ourhdr.h"

static void sig_int(int);
volatile sig_atomic_t quitflags;

int main(void){
        sigset_t newmask,oldmask,zeromask;

        if(signal(SIG))
}
