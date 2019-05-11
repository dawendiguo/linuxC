#include "ourhdr.h"

int main(int argc,char *argv[]){
        int status;

        if(argc != 2)
                err_quit("Usage: ./main <arguments>");

        if(status = system(argv[1]) < 0)
                err_sys("system() error");
        pr_exit(status);

        exit(0);
}
