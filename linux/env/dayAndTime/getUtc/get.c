#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int
main(void){
        time_t timeval;

        (void) time(&timeval);

        printf("The data of UTC is ：%lu\n",timeval);
        printf("The data of ctime is : %s\n",ctime(&timeval));
        exit(0);
}
