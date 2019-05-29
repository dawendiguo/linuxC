#include "ourhdr.h"
#include "my_abort.c"

int main(void){
        pid_t pid;
        int status;


        if((pid = fork()) < 0)
                err_sys("fork error");
        else if(pid == 0){
                my_abort();
        }
        else{
                printf("have a child : %d \n",wait(&status));
                pr_exit(status);
        }
        exit(0);
}
