#include "open.h"
#include <sys/uio.h>            /* struct iovec */

/* Open the file by sending the "name" and "oflag" to the 
 * connection server and reading a file descriptor back.*/

int 
csopen(char *name,int oflag){
        pid_t pid;
        int len;
        char buf[10];
        struct iovec iov[3];
        static int fd[2] = {-1,-1};
        if(fd[0] < 0){          /* fork/exec our openserver first time */
              if(s_pipe(fd) < 0)
                      err_sys("s_pipe error");
              if( (pid = fork()) < 0)
                      err_sys("fork error");
              else if(pid == 0){
                      close(fd[0]);
                      if(fd[1] != STDIN_FILENO){
                              if(dup2(fd[1],STDIN_FILENO) != STDIN_FILENO)
                                      err_sys("dup2 error to stdin");
                      }
                      if(fd[1] != STDOUT_FILENO){
                              if(dup2(fd[1],STDOUT_FILENO) != STDOUT_FILENO)
                                      err_sys("dup2 error to stdout");
                      }
                      if(execl("./server/opend","opend",NULL) < 0)
                              err_sys("execl error");
              }
              close(fd[1]);
        }

        sprintf(buf," %d",oflag);
        iov[0].iov_base = CL_OPEN " ";
        iov[0].iov_len = strlen(CL_OPEN) + 1;
        iov[1].iov_base = name;
        iov[1].iov_len = strlen(name);
        iov[2].iov_base = buf;
        iov[2].iov_len = strlen(buf)+1;       /* +1 for null at end of buf */
        len = iov[0].iov_len + iov[1].iov_len + iov[2].iov_len;

        if(writev(fd[0],&iov[0],3) != len)
                err_sys("writev error");

        /* read descriptor , returned errors handled by write() */
        return(recv_fd(fd[0],write));
}   
