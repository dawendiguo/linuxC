#include <errno.h>
#include "ourhdr.h"

static void pr_sysconf(char *mesg, int name);
static void pr_pathconf(char *mesg,char *path,int name);

int main(int argc,char *argv[])
{
    if(argc != 2)
        err_quit("Usage: a.out <dirname> ");
    pr_sysconf("ARG_MAX = ",_SC_ARG_MAX);
    pr_sysconf("CHILD_MAX = ",_SC_CHILD_MAX);
    pr_sysconf("clock ticks/second = ",_SC_CLK_TCK);
    pr_sysconf("NGROUPS_MAX = ",_SC_NGROUPS_MAX);
    pr_sysconf("OPEN_MAX = ",_SC_OPEN_MAX);
    #ifdef _SC_STREAM_MAX
    pr_sysconf("STREAM_MAX = ",_SC_STREAM_MAX);
    #endif
    #ifdef _SC_TZNAME_MAX
    pr_sysconf("TZNAME_MAX = ",_SC_TZNAME_MAX);
    #endif
    pr_sysconf("_POSIX_JOB_CONTROL = ",_SC_JOB_CONTROL);
    pr_sysconf("_POSIX_SAVED_IDS = ",_SC_SAVED_IDS);
    pr_sysconf("_POXI_VERSION = ",_SC_VERSION);
    pr_pathconf("_MAX_CANON = ","/dev/tty",_PC_MAX_CANON);
    pr_pathconf("_MAX_INPUT = ","/dev/tty",_PC_MAX_INPUT);
    pr_pathconf("_POSIX_VDISABLE = ","/dev/tty",_PC_VDISABLE);
    pr_pathconf("LINE_MAX = ",argv[1],_PC_LINK_MAX);
    pr_pathconf("NAME_MAX = ",argv[1],_PC_NAME_MAX);
    pr_pathconf("PATH_MAX = ",argv[1],_PC_PATH_MAX);
    pr_pathconf("PIPE_BUF = ",argv[1],_PC_PIPE_BUF);
    pr_pathconf("_POSIX_NO_TRUNC = ",argv[1],_PC_NO_TRUNC);
    pr_pathconf("_POSIX_CHOWN_RESTRICTED = ",argv[1],_PC_CHOWN_RESTRICTED);

    exit(0);
}
//get system variable
static void pr_sysconf(char *mesg, int name)
{
    long val;

    fputs(mesg,stdout);
    errno = 0;
    if( ( val = sysconf ( name ) ) < 0 ){
        //error get sysconf name
        if(errno != 0)
            err_sys("sysconf error");
        //get sysconf name successful, but is empty
        fputs("(not defined)\n",stdout);
    }
    //get system variable ,and not empty
    else{
        printf("%ld\n",val);
    }
}

//get path system max variable
static void pr_pathconf(char *mesg,char *path,int name)
{
    long val;
    
    fputs(mesg,stdout);
    errno = 0;
    if( ( val = pathconf ( path , name ) ) < 0){
        //system error
        if(errno != 0)
            err_sys("pathconf error, path = %s",path);
        //not define 
        else
            fputs("(No limit)\n",stdout);
    } 
    //get successful
    else{
        printf(" %ld\n",val);
    }
}
