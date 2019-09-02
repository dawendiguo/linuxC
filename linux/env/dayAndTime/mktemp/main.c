#include <stdlib.h>
#include <stdio.h>
#include "ourhdr.h"

int
main(){
        int fd;
        char temp_file[] = "Test_XXXXXX";

        if((fd = mkstemp(temp_file)) != -1)
                printf("create temporary file OK, and open it OK\n");
        else
                err_ret("create file error");

        if(write(fd,"qwe",3) != 3)
                err_sys("write err");

        close(fd);
        exit(0);
}
