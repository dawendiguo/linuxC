#include "ourhdr.h"

#define MAXARGC 50    /* max number of arguments in buf */
#define WHITE " \t\n" /* white space for tokenizing arguments */

/* buf[] contains white-space separated arguments. We convert it to an argv[] style array of pointers, and call the user's
 * function (*optfunc)() to process the argv() array.
 * We return -1 to the caller if there's a problem parsing buf,
 * else we return whatever optfunc() returns. Note that user's 
 * buf[] array is modified ( nulls placed after each token). */
int
buf_args(char *buf,int(*optfunc)(int,char **)){
        char *ptr,*argv[MAXARGC];
        int argc;

        if(strtok(buf,WHITE) == NULL)
                return(-1);
        argv[argc = 0] = buf;

        while((ptr = strtok(NULL,WHITE)) != NULL){
                if(++argc >= MAXARGC-1)     /* -1 for room for NULL at end */
                        return(-1);
                argv[argc] = ptr;
        }
        argv[++argc] = NULL;

        return((*optfunc)(argc,argv));
        /* Since argv[] pointers point into the user's buf[].
         * user's function can just copy the pointers, even
         * though argv[] array will disappear on return. */
}
