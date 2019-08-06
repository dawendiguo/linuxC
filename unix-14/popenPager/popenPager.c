#include <sys/wait.h>
#include "ourhdr.h"
#include "../myPopen/myPopen.c"

#define PAGER "${PAGER:-less}"

int
main(int argc,char *argv[]){
        char line[MAXLINE];
        FILE *fpin,*fpout;

        if(argc != 2)
                err_quit("usage: ./main <pathname>");

        if((fpin = fopen(argv[1],"r")) == NULL)
                err_sys("can't open %s",argv[1]);
        if((fpout = mypopen(PAGER,"w")) == NULL)
                err_sys("mypopen error");

        /* copy argv[1] to pager */
        while(fgets(line,MAXLINE,fpin) != NULL){
                if(fputs(line,fpout) == EOF)
                        err_sys("fputs error to pipe");
        }

        if(ferror(fpin))
                err_sys("fgets error");
        if(fclose(fpout) == -1)
                err_sys("mypclose error");
        exit(0);
}
