#include "ourhdr.h"
#include <sys/types.h>

int blod = 6;
char buf[] = " a write to stdout\n";

int main(void){
        int var;
        pid_t pid;
        int i;

        var = 88;
        if(write(STDOUT_FILENO,buf,sizeof(buf)-1) != sizeof(buf)-1)
                err_sys("write to stdout error");

        if(( pid = vfork()) < 0)
                err_sys("fork error!");
        else if(pid == 0){
                blod++;
                var++;
                _exit(0);
        }
        else
                sleep(2);

        i = printf("pid = %d,blod = %d,var = %d\n",getpid(),blod,var);
        sprintf( buf ,"%d\n",i);
        write(STDOUT_FILENO,buf,sizeof(buf));
        exit(0);
}
