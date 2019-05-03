#include "ourhdr.h"	
#include <errno.h>							// for definition of errno
#include <stdarg.h>							// ANSI C header file
#include <syslog.h>
#include<fcntl.h>                           //some method get system variable
#include<limits.h>                          //define some system variable 

//get system Open max
#ifdef OPEN_MAX
//system define open max
static int openmax=OPEN_MAX;
#else
//system not define open max
static int openmax=0;
#endif
//open max guess if system not define oopen max
#define OPEN_MAX_GUESS 256;

//get path name max size
#ifdef _PC_PATH_MAX
//system define path name max size
static int pathmax=_PC_PATH_MAX;
#else
//system not define path name max size,we set it to 0, we will give it to a guess size save the path name.
static int pathmax=0;
#endif
// path name guess size
#define PATH_MAX_GUESS 1024;

static void err_doit(int,const char*,va_list);              //err println function common used function

char *pname=NULL;												// caller can set this from Argv[0]
extern int debug=1;											// caller must define and set this: nonzero if interactive ,aero if daemon

/* Nonfatal error related to a system call,
 * Print a message and return. */
void err_ret(const char *fmt, ...){
    va_list ap;
    va_start(ap,fmt);
    err_doit(1,fmt,ap);
    va_end(ap);
    return;
}

/* Fatal error related to a system call.
 * Print a message and terminate.*/
void err_sys(const char *fmt, ...){
	va_list ap;
	va_start(ap,fmt);
	err_doit(1,fmt,ap);
	va_end(ap);
	exit(1);
}

/* Fatal error related to a system call.
 * Print a message, dump core, and terminate.*/
void 
err_dump(const char *fmt, ...){
	va_list ap;
	va_start(ap,fmt);
	err_doit(1,fmt,ap);
	va_end(ap);
	abort();		//dump core and terminate
	exit(1);		// shouldn't get here
}

/* Nonfatal error unrelated to a system call.
 * Print a message and return.*/
void 
err_msg(const char *fmt, ...){
	va_list ap;
	va_start(ap,fmt);
	err_doit(0,fmt,ap);
	va_end(ap);
	return;
}

/* Fatal error unrelated to a system call.
 * Print a message and terminate.*/
void 
err_quit(const char *fmt, ...){
	va_list ap;
	va_start(ap,fmt);
	err_doit(0,fmt,ap);
	va_end(ap);
	exit(1);
}

/* Print a message and return to caller.
 * Caller specifies "arrnoflag".*/
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

static void log_doit(int,int,const char*, va_list ap);      //log err common use function

// Initialize syslog(), is running as daemon.
void 
log_open(const char *ident,int option,int facility){
	if(debug == 0 )
		openlog(ident,option,facility);
}

/* Nonfatal error related to a system call.
 * Print a message whith the system's errno value and return.*/
void 
log_ret(const char *fmt, ...){
	va_list ap;
	
	va_start(ap,fmt);
	log_doit(1,LOG_ERR,fmt,ap);
	va_end(ap);
	return;
}

/* Fatal error related to aa system call.
 * Print a message and terminate.*/
void 
log_sys(const char *fmt, ...){
	va_list ap;

	va_start(ap,fmt);
	log_doit(1,LOG_ERR,fmt,ap);
	va_end(ap);
	exit(2);
}

/*Nonfatal error unrelated to a system call.
 * Print a message and return.*/
void 
log_msg(const char *fmt, ...){
	va_list ap;

	va_start(ap,fmt);
	log_doit(0,LOG_ERR,fmt,ap);
	va_end(ap);
	return;
}

/* Fatal error unrelated to system call.
 * Print a message and terminate.*/
void 
log_quit(const char *fmt, ...){
	va_list ap;

	va_start(ap,fmt);
	log_doit(0,LOG_ERR,fmt,ap);
	va_end(ap);
	exit(2);
}

/* Print a message and return to caller.
 * Caller specifies "errnoflag" and "priority".*/
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

//alloc memery for save path name
char *
path_alloc(long *size){            //also return allocated size, if nonnull
   
   char *ptr;
    if(pathmax==0){                     //system not define path max size
        errno=0;
        if((pathmax=pathconf("/",_PC_PATH_MAX))<0)      //system not set path max ,this will shuld run.path max get size "/" directory path size.if "/" not null. < 0 content not set.
                {
                    if(errno == 0)              // no error
                    {
                    pathmax=PATH_MAX_GUESS;
                    }
                    else{                       // get "/" directory path_max error
                    err_sys("pathconf error for _PC_PATH_MAX");
                    }
                }
        else                                    //if run this pathmx is "/" directory path max
                pathmax++;
    }
    if((ptr=malloc(pathmax+1)) == NULL)
        err_sys("malloc error for pathname");
    if(size != NULL)
        *size=pathmax+1;
    return(ptr);                                    //return point for save path name
}

void set_fl(int fd,int flags)  // flags are file status flags to turn on
{
    //val for save current status
    int val;
    //fcntl get current status
    if((val = fcntl(fd,F_GETFL,0))<0)
        err_sys("fcntl F_GETFL error");
    //change status use flags    
    val |= flags;
    //set val into file 
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

//get program can open max program
int open_max(void){
    //system not define open max
   if(openmax == 0){
   errno=0;
   if((openmax=sysconf(_SC_OPEN_MAX))<0){       //get system open max.when not set do if
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
