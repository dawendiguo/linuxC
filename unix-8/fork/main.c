#include "ourhdr.h"
#include <sys/types.h>

int golb = 6;
char buf[] = " a write to stdout\n";

int main(void){ 

        int var;
        pid_t pid;

        var = 88;
        if(write(STDOUT_FILENO,buf,sizeof(buf)-1) != sizeof(buf)-1)
                err_sys("write error");
        printf("before fork\n");

        if((pid = fork()) < 0)
              err_sys("fork error");
        else if(pid == 0){  
                golb++;
                var++;
        }
        else
                sleep(2);

        printf("pid = %d ,golb = %d,var = %d\n",getpid(),golb,var);
        exit(0);
}
