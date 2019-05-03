#include "ourhdr.h"

int main(void){
    char *ptr;
    long size;

    if(chdir("next") < 0)
        err_sys("chdir failed");
   // ptr = path_alloc(&size);             //path ptr create
  // printf(" MAX PATH NAME %d \n",ptr);
   if((ptr = getcwd(NULL,0)) == NULL)
        err_sys("getcwd failed");
    
    printf("cwd = %s \n",ptr);
    free(ptr);

while(1){
    if( mkdir ("next",600) < 0)
        err_sys("mkdir error");
    if(chdir("next") < 0)
        err_sys("chdir failed");
   if((ptr = getcwd(NULL,0)) == NULL)
        err_sys("getcwd failed");
    
    printf("cwd = %s \n",ptr);
    free(ptr);
}
    exit(0);
}
