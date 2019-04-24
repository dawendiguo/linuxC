#include "ourhdr.h"
#include <sys/types.h>
#include <fcntl.h>

#define BUFFSIZE 50

int main(int argc,char *argv[]){
	int n;
	char buf[BUFFSIZE];
    int outputFile;
    if(argc != 2){
    err_quit("Usage: main <fileSystem>");
    }
    if((outputFile = creat(argv[1],FILE_MODE)) < 0){
    err_sys("creat file error!");
    }
	while( ( n = read(STDIN_FILENO,buf,BUFFSIZE) ) > 0){
        if(write(outputFile,buf,n) != n)
            err_sys("write error");

    }
    if(n < 0){
    err_sys("read error");
    }
    exit(0);
}
