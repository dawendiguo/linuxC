#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
        struct tm *tm_ptr, timestruct;
        time_t timevalue;
        char buf[256];
        char *result;

        (void)time(&timevalue);
        tm_ptr = localtime(&timevalue);
        strftime(buf,256,"%A %d %B, %I:%s %p",tm_ptr);

        printf("strftime gives: %s\n",buf);

        strcpy(buf,"Thu 26 July 2007, 17:53 will do fine");
        tm_ptr = &timestruct;

        strptime(buf,"%a %d %b %Y, %R", tm_ptr);
       // printf("strptime consumed up to : %s\n",result);

        printf("strptime gives: \n");
        printf("date: %02d/%02d/%02d\n",
                        tm_ptr->tm_year+1900,tm_ptr->tm_mon+1,tm_ptr->tm_mday);
        printf("Time: %02d:%02d\n",
                        tm_ptr->tm_hour,tm_ptr->tm_sec);
}
