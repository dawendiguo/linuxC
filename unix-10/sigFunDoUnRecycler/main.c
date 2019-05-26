#include <pwd.h>
#include <signal.h>
#include "ourhdr.h"

static void my_alarm(int);

int main(void){
        struct passwd *ptr;

        signal(SIGALRM,my_alarm);
        alarm(1);

        for(;;){
                if( (ptr = getpwnam("html")) == NULL)
                        err_sys("getpwname error");
                if(strcmp(ptr->pw_name, "html") != 0)
                        printf("return value corrupted!, pw_name = %s \n",
                                        ptr->pw_name);
        }
}

static void my_alarm(int signo){
      struct passwd *rootptr;

      printf("in signal handler\n");
      printf("other title");
      if( (rootptr = getpwnam("root")) == NULL)
              err_sys("getpwname(root) error");
      printf("in signal handler name is %s \n",rootptr->pw_name);
      alarm(1);
      return;
}
