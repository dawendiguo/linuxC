#include "ourhdr.h"
int main(void){
        pid_t pid;

        if((pid = fork()) < 0)
                err_sys("fork error");
        else if( pid == 0)
                _exit(0);
       else if(pid > 0){

        system("ps");
        sleep(2);
       }
}
