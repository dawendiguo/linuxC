#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "ourhdr.h"

const char *file = "/tmp/test_lock";

int
main(){
        int fd;
        struct flock region_to_lock;

        if((fd = open(file,O_RDWR | O_CREAT,0666)) == -1)
                err_sys("open error for %s",file);

        region_to_lock.l_type = F_RDLCK;
        region_to_lock.l_whence = SEEK_SET;
        region_to_lock.l_start = 10;
        region_to_lock.l_len = 5;

        printf("Process %d, trying F_RDLCK, region %d to %d\n",getpid(),
                       (int)region_to_lock.l_start,(int)region_to_lock.l_start + (int)region_to_lock.l_len);

        if((fcntl(fd,F_SETLK,&region_to_lock)) == -1)
                printf("Process %d - failed to lock region\n",getpid());
        else
                printf("Process %d - obtained to region\n",getpid());

        region_to_lock.l_type = F_UNLCK;
        region_to_lock.l_whence = SEEK_SET;
        region_to_lock.l_start = 10;
        region_to_lock.l_len = 5;

        printf("Process %d, trying F_UNLCK, region %d to %d \n",getpid(),
                       (int)region_to_lock.l_start,(int)region_to_lock.l_start + (int)region_to_lock.l_len);

        if((fcntl(fd,F_SETLK,&region_to_lock)) == -1)
                printf("Process %d - failed to unlock region\n",getpid());
        else
                printf("Process %d - unlock region\n",getpid());

        region_to_lock.l_type = F_WRLCK;
        region_to_lock.l_whence = SEEK_SET;
        region_to_lock.l_start = 16;
        region_to_lock.l_len = 5;

        printf("Process %d, trying F_WRLCK, region %d to %d\n",getpid(),
                       (int)region_to_lock.l_start,(int)region_to_lock.l_start + (int)region_to_lock.l_len);

        if((fcntl(fd,F_SETLK,&region_to_lock)) == -1)
                printf("Process %d - failed to lock region\n",getpid());
        else
                printf("Process %d - obtained to region\n",getpid());

        region_to_lock.l_type = F_RDLCK;
        region_to_lock.l_whence = SEEK_SET;
        region_to_lock.l_start = 40;
        region_to_lock.l_len = 10;

        printf("Process %d, trying F_RDLCK, region %d to %d\n",getpid(),
                       (int)region_to_lock.l_start,(int)region_to_lock.l_start + (int)region_to_lock.l_len);

        if((fcntl(fd,F_SETLK,&region_to_lock)) == -1)
                printf("Process %d - failed to lock region\n",getpid());
        else
                printf("Process %d - obtained to region\n",getpid());

        region_to_lock.l_type = F_WRLCK;
        region_to_lock.l_whence = SEEK_SET;
        region_to_lock.l_start = 16;
        region_to_lock.l_len = 5;

        printf("Process %d, trying F_WRLCK, region %d to %d\n",getpid(),
                       (int)region_to_lock.l_start,(int)region_to_lock.l_start + (int)region_to_lock.l_len);

        if((fcntl(fd,F_SETLK,&region_to_lock)) == -1)
                printf("Process %d - failed to lock region\n",getpid());
        else
                printf("Process %d - obtained to region\n",getpid());

        printf("Process %d ending\n",getpid());
        close(fd);
        exit(0);
}
