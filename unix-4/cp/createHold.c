#include "ourhdr.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

char buf1[] = "abcdefghij";
char buf2[] = "dawendiguo";
int main(void){
    int fd;

    if( ( fd = creat("file.hold",FILE_MODE) ) < 0){
    err_sys("creat error");
    }

    if(write(fd,buf1,10) != 10){
    err_sys("write error");                                 //  current offset  is 10
    }

    if(lseek(fd,40,SEEK_SET) == -1){
    err_sys("lseed error");
    }

    if(write(fd,buf2,10) != 10){
    err_sys("write error");                                 //current offset is 50
    }
}
