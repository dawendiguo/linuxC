#include "ourhdr.h"

int main(void){
    FILE *fp ;

    fputs("enter any characters\n",stdout);
    if(getchar() == EOF)
        err_sys("getchar error");
    fputs("one line to standard error\n",stderr);

    pr_stdio("stdin",stdin);
    pr_stdio("stdout",stdout);
    pr_stdio("stderr",stderr);

    if( (fp = fopen("/etc/motd","r")) == NULL)
        err_sys("open error");
   pr_stdio("/etc/motd",fp);
   if(getc(fp) == EOF)  
        err_sys("getc error");
    exit(0);
}

pr_stdio(const char *name,FILE *fp){
    printf("stream = %s ",name);

    if(fp->_flags & _IONBF)  printf("unbuffered");
    else if( fp->_flags & _IOLBF )  printf("line buffered");
    else   printf("full buffered");
    printf(" , buffer size : %d \n",fp->_fileno);
}
