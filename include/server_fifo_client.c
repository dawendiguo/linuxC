#include "ourhdr.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>

/* Create a server endpoint of connection. */

int       /* return fd if all ok, <0 on error */
serv_listen(const char *name){
        int fd,len;
        struct sockaddr_un unix_addr;

        /* Create a Unix domain stream socket */
        if((fd = socket(AF_UNIX,SOCK_STREAM,0)) < 0)
                return(-1);

        unlink(name);      /* in case it already exists */

        /* fill in socket address structure */
}
