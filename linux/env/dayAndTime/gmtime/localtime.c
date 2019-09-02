#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int 
main(void){
        time_t timeval;
        struct tm *tm_opt;

        (void)time(&timeval);
        tm_opt = localtime(&timeval);


        printf("Year:%03d,month:%02d,day:%02d\n",
                        tm_opt->tm_year+1900,tm_opt->tm_mon+1,tm_opt->tm_mday);
        printf("H:%02d,M:%02d,S:%02d\n",tm_opt->tm_hour,tm_opt->tm_min,tm_opt->tm_sec);
        exit(0);
}
