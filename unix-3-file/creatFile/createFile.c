#include "ourhdr.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc,char *argv[]){
    if(argc != 2){
    err_quit("Usage: main <fileName> ");
    }

    int fd;
    if(( fd = creat(argv[1],FILE_MODE)) < 0){
        err_sys("create error");
    }
}
