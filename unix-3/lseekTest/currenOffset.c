#include "ourhdr.h"
#include <sys/stat.h>
#include <sys/types.h>

int main(void){

    if(lseek(STDIN_FILENO,0,SEEK_CUR) == -1){
    err_sys("lseek error");
    }
    else{
    printf("lseek OK\n");
    }
}
