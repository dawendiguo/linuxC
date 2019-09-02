#include <time.h>
#include <stdio.h>
#include <stdlib.h>

/* gmtime : get struct tm, amd use printf show it */
int
main(void){
        time_t timeval;
        struct tm *tm_opt;


        (void)time(&timeval);
        tm_opt = gmtime(&timeval);

        printf("Raw time is %d\n",(int)timeval);
        printf("gmtime gives:\n");
        printf("data: %02d/%02d/%02d\n",tm_opt->tm_year,tm_opt->tm_mon,tm_opt->tm_mday);
        printf("time: %02d:%02d:%02d\n",tm_opt->tm_hour,tm_opt->tm_min,tm_opt->tm_sec);
        exit(0);
}
