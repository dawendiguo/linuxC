#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "ourhdr.h"

const char *file = "/tmp/test_lock";

int main(){
        int fd;
        int byte_count;
        char *byte_to_write = "A";
        struct flock region_1;
        struct flock region_2;

       if( (fd = open(file,O_RDWR|O_CREAT,0666)) == -1)
               err_sys("Unable to open %s for read/write\n",file);

       /* write 100 byte to file */
       for( byte_count = 0; byte_count < 100; byte_count++)
               if(write(fd,byte_to_write,1) != 1)
                       err_sys("write error");

       /* construction structure flock  1 */
       /* 10 ~ 30 byte , share lock (read lock) */
       region_1.l_type = F_RDLCK;
       region_1.l_whence = SEEK_SET;
       region_1.l_start = 10;
       region_1.l_len = 30;

       /* construction structure flock 2 */
       /* 40 ~ 50 byte, monopolize lock */
       region_2.l_type = F_WRLCK;
       region_2.l_whence = SEEK_SET;
       region_2.l_start = 40;
       region_2.l_len = 10;

       /* set the two lock */
       if((fcntl(fd,F_SETLK,&region_1)) == -1)
               err_sys("Failed to lock region 1\n");
       if((fcntl(fd,F_SETLK,&region_2)) == -1)
               err_sys("Failed to lock region 2\n");

       /* wait other process read the two lock */
       sleep(60);

       printf("Process %d closing file\n",getpid());
       close(fd);
       exit(0);
}
