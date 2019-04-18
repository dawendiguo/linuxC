#include "ourhdr.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc,char *argv[]){
    //index of arguments;
    int i;

    //usage,arguments numbers
    if(argc == 1){
        err_sys(" Usage : main filenames ......");
    }
    else{
        for(i=1;i<argc;i++){
            if(open(argv[i],O_CREAT|O_TRUNC|O_WRONLY)<0){
                err_ret("open error!");
                continue;
            }
        }
    }
    exit(0);
}
