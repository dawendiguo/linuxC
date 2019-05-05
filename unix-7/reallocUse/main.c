#include "ourhdr.h"

char *str="only a test";

int main(void){
        char *ptr;
        ptr=(char *)malloc(strlen(str)+1);

        strcpy(ptr,str);
        printf("ptr string; %s\n",ptr);
        //decrease ptr size
        if(realloc(ptr,3) == NULL)  
                err_sys("error");
        printf("ptr string; %s\n",ptr);
        exit(0);
        
}
