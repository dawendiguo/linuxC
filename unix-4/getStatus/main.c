#include "ourhdr.h"
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc,char *argv[]){
    //index for file
    int i;
    //buf for save current stat
    struct stat buf;
    //string for save file mode 
    char *ptr;
    
    //if argument no only one
    if(argc == 1){
        err_quit("Usage main <files> ......");
    }
    else{
        //file is from argv[1]
        for(i = 1; i < argc; i++){
            //get stat struct,save into buf not to return val,use &buf not buf.
            if( lstat(argv[i],&buf) < 0){
                //not fatal so continue
                err_ret("lstat error");
                continue;
            }
            //juge type,use system macro.
            if( S_ISREG(buf.st_mode) )      ptr = "regular";    //save mode string into ptr
            else if( S_ISDIR(buf.st_mode) ) ptr = "directory";
            else if( S_ISCHR(buf.st_mode) ) ptr = "character specil";
            else if( S_ISBLK(buf.st_mode) ) ptr = "block special";
            //system define s_ISLNK
            #ifdef S_ISLNK
                else if( S_ISLNK(buf.st_mode) ) ptr = "symbolic link";
            #endif
            //system define S_ISSOCK
            #ifdef S_ISSOCK
                else if( S_ISSOCK(buf.st_mode) ) ptr = "socket";
            #endif
            //unknown file
            else
                ptr = "unknown file";
            //output mode string
            printf("%s\n",ptr);
        }
        exit(0);
    }
}
