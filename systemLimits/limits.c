#include<stdio.h>
#include<limits.h>
#include<errno.h>
#include "ourhdr.h"

static void pr_systemconf(char *,int);
static void pr_pathconf(char *,char *,int);

int main(int argc,char *argv[]){
    if(argc!=2)
        err_quit("usage: main <dirent name>");
    pr_systemconf("ARG_MAX:",_SC_ARG_MAX);
    pr_systemconf("CHILD_MAX:",_SC_CHILD_MAX);
   pr_systemconf("clock ticks/seconds",_SC_CLK_TCK);
   pr_systemconf("NGROUP_MAX:",_SC_NGROUPS_MAX);
   pr_systemconf("OPEN_MAX:",_SC_OPEN_MAX);
    #ifdef  _SC_STREAM_MAX
        pr_systemconf("STEAME_MAX:",_SC_STREAM_MAX);
#endif
   #ifdef _SC_TZNAME_MAX
        pr_systemconf("TZNAME_MAX:",_SC_TZNAME_MAX);
#endif
        pr_systemconf("_POSIX_JOB_CONTROL:",_SC_JOB_CONTROL);
        pr_systemconf("_POSIX_SAVED_IDS:",_SC_SAVED_IDS);
        pr_systemconf("_POSIX_VERSION:",_SC_VERSION);
        pr_pathconf("MAX_CANON:","dev/tty",_PC_MAX_CANON);
        pr_pathconf("MAX_INPUT:","dev/tty",_PC_MAX_INPUT);
        pr_pathconf("LINK_MAX:",argv[1],_PC_LINK_MAX);
        pr_pathconf("NAME_MAX:",argv[1],_PC_NAME_MAX);
        pr_pathconf("PATH_MAX:",argv[1],_PC_PATH_MAX);
        pr_pathconf("PIPE_BUF:",argv[1],_PC_PIPE_BUF);
        pr_pathconf("POSIX_NO_TRUNC:",argv[1],_PC_NO_TRUNC);
        exit(0);
}

static void pr_systemconf(char *mesg,int name){
    long val;
    fputs(mesg,stdout);
    errno = 0;
    if((val=sysconf(name)) < 0){
        if(errno != 0)
            err_sys("system error");
        fputs("not defined \n",stdout);
    }else
        printf("%ld\n",val);
}

static void pr_pathconf(char *mesg,char *path,int name){
    long val;
    fputs(mesg,stdout);
    errno=0;
    if((val=pathconf(path,name))<0){
        if(errno!=0)
            err_sys("system error");
        fputs("not defined\n",stdout);
    }else
        printf("%ld\n",val);
}
