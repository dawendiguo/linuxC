#include "ourhdr.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <limits.h>

typedef int Myfunc(const char *,const struct *,int);
    //function type that's called for each filename
static Myfunc myfunc;
static int myftw(char *,Myfunc *);
static int dopath(Myfunc *);

static long nreg,ndir,nblk,nchr,nfifo,nslink,nsock,ntot;

int main(int argc,char *argv[]){
    int ret;

    if(argc !=2){
        err_sys("Usage: man <starting-pathname>");
    }

    ret = myftw(argv[1],myfunc);

    if( (ntot = nreg + ndir + nblk + nchr + nfifo + nslink + nsock ) == 0){
        ntot = 1;           //avoid divide by 0,print 0 for all counts;
    }
    printf("regular flies = %71d,%5.2f %%\n",nreg,nreg*100.0/ntot);
    printf("directories flies = %71d,%5.2f %%\n",ndir,ndir*100.0/ntot);
    printf("block special flies = %71d,%5.2f %%\n",nblk,nblk*100.0/ntot);
    printf("char special flies = %71d,%5.2f %%\n",nchr,nchr*100.0/ntot);
    printf("FIFOs flies = %71d,%5.2f %%\n",nfifo,nfifo*100.0/ntot);
    printf("symbollic flies = %71d,%5.2f %%\n",nslink,nslink*100.0/ntot);
    printf("sockets flies = %71d,%5.2f %%\n",nsock,nsock*100.0/ntot);A

    exit(ret);
}

/*
 * Descend through the hierarchy, starting at pathname.
 * The caller's func() is called for ervery file.
 */
#define FTW_F 1     //file other than directory
#define FTW_D 2     //directory
#define FTW_DNR 3   //directory that can't be read
#define FTW_NS 4    //file that we can't stat

static char *fullpath       //contain full pathname for ervery file
    
static int                  //we return whatever func() returns
myftw(char *pathname,Myfunc *func){
    fullpath = path_alloc(NULL);            //malloc's for PATH_MAX+1 bytes     define in ourhdr.h

    strcpy(fullpath,pathname);              //initialize fullpath

    return (dopath(func));
}

/*
 * Descend through the hierarchy, starting at fullpath
 * if "fullpath" is anthing other than a directory, we lstat() it,
 * call func(), and return. For a directory, we call ourself
 * recursively for each name in the directory.
 */
static int                  //we return whaterver func returns
dopath(Myfunc* func){
    struct stat statbuf;
    struct dirent *dirp;
    DIR *dp;
    int ret;
    char *ptr;

    if(lstat(fullpath,&statbuf) < 0)
        return(func(fullpath, &statbuf, FTW_NS));       //STAT ERROR
         
}
