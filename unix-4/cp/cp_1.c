#include "ourhdr.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc,char* argv[]){

    int c;

    int file1;
    int file2;
    char buf[1];        //只读取写入一个字符

    if(argc != 3){
        err_dump("Usage: main inputFile outputFile.");
    }
    if( (file1 = open(argv[1],O_RDONLY)) < 0){
        err_sys("open %s error",argv[1]);
    }
    if( (file2 = open(argv[2],O_WRONLY|O_CREAT|O_TRUNC)) < 0){
        err_sys("open %s error",argv[2]);
    }

    //read input file
    while ( (c = read(file1,buf,1)) > 0 )
    {
        if( buf[0] != 0 ){
        //write to output file
        if( (write(file2,buf,1)) != 1){
            err_sys("write error!");
        }
        }
        else{
            continue;
        }
    }
    if ( c < 0 )
        err_sys( "read %s error",argv[1]);
    exit(0);
}
