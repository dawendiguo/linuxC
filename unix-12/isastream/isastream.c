#include <unistd.h>
#include <sys/ioctl.h>

int
isastream(int fd){
        return(ioctl(fd,I_CANPUT,0) != -1);
}
