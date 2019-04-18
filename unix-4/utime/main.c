#include "ourhdr.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <utime.h>

int main(int argc,char *argv[]){

    int i;
    struct stat statbuf;
    struct utimbuf timebuf;

    for(i=1;i<argc;i++){    
        //get stat buf 
        if( stat(argv[i],&statbuf) < 0)
        {
            //next file
            err_ret("system stat error");
            continue;
        }
        //open file change atime
        if( open(argv[i],O_RDWR|O_TRUNC) < 0 )
        {
            //open error next one
            err_ret("system open error");
            continue;
        }

        //get old atime and mtime
        timebuf.actime = statbuf.st_atime;
        timebuf.modtime = statbuf.st_mtime;

        //set utim to old time
        if( utime(argv[i],&timebuf) < 0){
        err_ret("utime error");
        continue;
        }
    }
    exit(0);
}
