#include "ourhdr.h"	
#include <errno.h>
#include <stdarg.h>
#include <syslog.h>

static void err_doit(int,const char*,va_list);
char *pname=NULL;
extern int debug=1;

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
