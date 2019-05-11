#include <sys/types.h>
#include "ourhdr.h"

static void showchracter(char *);

int main(void){
    pid_t pid;

    if( (pid = fork()) < 0)
            err_sys("fork error!");
    else if(pid > 0)
            showchracter("output from parent\n");
    else
            showchracter("output from child\n");
    exit(0);
}

static void showchracter(char *string){
    char *ptr;
    int c;

    setbuf(stdout,NULL);

    for(ptr = string; c = *ptr++;)
            putc(c,stdout);
}
