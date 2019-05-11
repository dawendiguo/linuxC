#include "ourhdr.h"
#include <stdlib.h>

void getArgument(void);
int main(int argc,char *argv[]){
    if(setenv("argv",argv[0],1) != 0)
            err_sys("setenv errror");
    getArgument();
    if(unsetenv("argv") != 0)
            err_sys("unsetenv error");
    getArgument();
    exit(0);
}

void getArgument(void){
        printf("argv : %s \n",getenv("argv"));
}
