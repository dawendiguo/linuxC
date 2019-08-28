#include <stdio.h>
#include <stdlib.h>

#define BASIC_DEBUG 1
#define EXTRA_DEBUG 2
#define SUPER_DEBUG 4

int main(){
#ifdef DEBUG
        printf("DEBUG is open\n");
        if(DEBUG & EXTRA_DEBUG){
                printf("open EXTRA_DEBUG\n");
        }
        if(DEBUG & BASIC_DEBUG){
                printf("open BASIC_DEBUG\n");
        }
        if(DEBUG & SUPER_DEBUG){
                printf("open SUPER_DEBUG\n");
        }
#endif

#ifdef DEBUG
        printf("Compiled: "__DATE__"_TIME_"__TIME__"\n");
        printf("This is line %d of file %s\n",__LINE__,__FILE__);
#endif
        printf("hello world \n");
        exit(0);
}
