#include "ourhdr.h"	
#include <errno.h>
#include <stdarg.h>
#include <syslog.h>
#include<fcntl.h>
#include<limits.h>

#ifdef OPEN_MAX
static int openmax=OPEN_MAX;
#else
static int openmax=0;
#endif

#define OPEN_MAX_GUESS 256;

#ifdef _PC_PATH_MAX
static int pathmax=_PC_PATH_MAX;
#else
static int pathmax=0;
#endif

#define PATH_MAX_GUESS 1024;
static void err_doit(int,const char*,va_list);
char *pname=NULL;
extern int debug=1;

void err_ret(const char *fmt, ...){
    va_list ap;
    va_start(ap,fmt);
    err_doit(1,fmt,ap);
    va_end(ap);
    return;
}

void 
err_sys(const char *fmt, ...){
	va_list ap;
	va_start(ap,fmt);
	err_doit(1,fmt,ap);
	va_end(ap);
	exit(1);
}


void 
err_dump(const char *fmt, ...){
	va_list ap;
	va_start(ap,fmt);
	err_doit(1,fmt,ap);
	va_end(ap);
	abort();
	exit(1);
}


void 
err_msg(const char *fmt, ...){
	va_list ap;
	va_start(ap,fmt);
	err_doit(0,fmt,ap);
	va_end(ap);
	return;
}

void 
err_quit(const char *fmt, ...){
	va_list ap;
	va_start(ap,fmt);
	err_doit(0,fmt,ap);
	va_end(ap);
	exit(1);
}

static void 
err_doit(int errnoflag,const char *fmt, va_list ap){
	int errno_save;
	char buf[MAXLINE];

	errno_save = errno;
	vsprintf(buf,fmt,ap);
	if(errnoflag)
		sprintf(buf+strlen(buf), ": %s",strerror(errno_save));
	strcat(buf,"\n");
	fflush(stdout);
	fputs(buf,stderr);
	fflush(NULL);
	return;
}

static void log_doit(int,int,const char*, va_list ap);


void 
log_open(const char *ident,int option,int facility){
	if(debug == 0 )
		openlog(ident,option,facility);
}

void 
log_ret(const char *fmt, ...){
	va_list ap;
	
	va_start(ap,fmt);
	log_doit(1,LOG_ERR,fmt,ap);
	va_end(ap);
	return;
}

void 
log_sys(const char *fmt, ...){
	va_list ap;

	va_start(ap,fmt);
	log_doit(1,LOG_ERR,fmt,ap);
	va_end(ap);
	exit(2);
}

void 
log_msg(const char *fmt, ...){
	va_list ap;

	va_start(ap,fmt);
	log_doit(0,LOG_ERR,fmt,ap);
	va_end(ap);
	return;
}

void 
log_quit(const char *fmt, ...){
	va_list ap;

	va_start(ap,fmt);
	log_doit(0,LOG_ERR,fmt,ap);
	va_end(ap);
	exit(2);
}

static void 
log_doit(int errnoflag, int priority, const char *fmt, va_list ap){
	int errno_save;
	char buf[MAXLINE];

	errno_save=errno;

	vsprintf(buf,fmt,ap);
	if(errnoflag)
		sprintf(buf+strlen(buf), ": %s",strerror(errno_save));
	strcat(buf,"\n");
	if(debug){
		fflush(stdout);
		fputs(buf,stderr);
		fflush(stderr);
	}else
		syslog(priority,buf);
	return;
}

void pr_exit(int status)
{
	if(WIFEXITED(status))
		printf("nomal termination,exit status = %d\n",WEXITSTATUS(status));
	else if(WIFSIGNALED(status))
		printf("abnormal termination, signal number = %d%s\n",WTERMSIG(status),
#ifdef WCOREDUMP
				WCOREDUMP(status) ? "(core fule.generated)":"");
#else
	"");
#endif
	else if(WIFSTOPPED(status))
		printf("child stopped, signal number = %d\n",WSTOPSIG(status));
}

char *path_alloc(int *size){
    char *ptr;
    if(pathmax==0){
        errno=0;
        if((pathmax=pathconf("/",_PC_PATH_MAX))<0)
                {
                    if(errno == 0)
                    {
                pathmax=PATH_MAX_GUESS;

                    }
                else{
                err_sys("pathconf error for _PC_PATH_MAX");
                }
                }
        else
                pathmax++;
        }
    if((ptr=malloc(pathmax+1))==NULL)
        err_sys("malloc error for pathname");
    if(size != NULL)
        *size=pathmax+1;
    return(ptr);
}

void set_fl(int fd,int flags)  // flags are file status flags to turn on
{
    int val;
    if((val = fcntl(fd,F_GETFL,0))<0)
        err_sys("fcntl F_GETFL error");
    val |= flags;
    if(fcntl(fd,F_SETFL,val)<0)
        err_sys("fcntl F_SETFL error");
}

void crl_fl(int fd,int flags)  // flags are file status flags to turn on
{
    int val;
    if((val = fcntl(fd,F_GETFL,0))<0)
        err_sys("fcntl F_GETFL error");
    val &= ~flags;
    if(fcntl(fd,F_SETFL,val)<0)
        err_sys("fcntl F_SETFL error");
}
int open_max(void){
   if(openmax == 0){
   errno=0;
   if((openmax=sysconf(_SC_OPEN_MAX))<0){
        if(errno == 0)
        {
   openmax=OPEN_MAX_GUESS;
        }
        else{
   err_sys("sysconf error for _SC_OPEN_MAX");
        }
   }
   }
   return(openmax);
}
