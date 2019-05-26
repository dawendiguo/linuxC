/*
 * 演示sleep2()函数的bug。
 */

#include <signal.h>
#include "sleep2.c"
#include "ourhdr.h"

//unsigned int sleep2(unsigned int);
static void sig_int(int);

int main(void){
        unsigned int unslept;

        if(signal(SIGINT,sig_int) == SIG_ERR)
                err_sys("signal(SIGINT)error\n");

        unslept = sleep2(5);
        printf("sleep2 returned %u\n",unslept);

        exit(2);
}

static void sig_int(int signo){
        volatile int i;
        volatile int j;

        printf("\n sig_int starting\n");
        for(i = 0;i < 2000000000; i++){

                j = j + i * i;
                //printf("Current j %d \n",j);
        }
        printf("sig_int finishing\n");
        return;
}
