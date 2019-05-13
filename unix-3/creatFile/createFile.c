#include "ourhdr.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc,char *argv[1]){
    if(argc != 3){
    err_quit("Usage: main <fileName>");
    }

    int fd ;
    if((fd = creat(argv[1],FILE_MODE)) < 0){
    err_sys("create error");
    }
    if((fd = open(argv[2],O_WRONLY|O_TRUNC|O_CREAT,FILE_MODE)) < 0)
        err_sys("open method create file error");
    close(fd);
}
