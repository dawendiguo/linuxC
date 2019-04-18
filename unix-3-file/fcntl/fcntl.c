#include  "ourhdr.h"
#include <sys/types.h>
#include <fcntl.h>

int main(int argc,char *argv[]){    
    int accmode , val;

    if(argc != 2){
        err_quit("Usage main <descriptor>");
    }
  
  if(( val = fcntl(atoi(argv[1]),F_GETFL,0) ) < 0){
    err_sys("fcntl error");
  }

   putchar(val);
  accmode = val & O_ACCMODE;

  if(accmode == O_RDONLY)   printf("只读");
 else if(accmode == O_WRONLY)  printf("只写");
 else if(accmode == O_RDWR)   printf("读写都可以");
 else
    printf("Unknow access mode");

 if(val&O_APPEND)      printf(",追加");
 if(val&O_NONBLOCK) printf(",不阻塞");
 #if !defined(_POSIX_SOURCE) && defined(O_SYNC)
    if(val & O_SYNC)    printf(",同步");
#endif
putchar('\n');
exit(0);
}
