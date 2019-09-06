#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "ourhdr.h"

const char *file = "/tmp/test_lock";
#define SIZE_TO_TRY 5

void show_lock_info(struct flock *to_show);

int
main(){
        int fd;
        struct flock region_to_test;
        int start_byte;

        if((fd = open(file,O_RDWR|O_CREAT,0666)) == -1)
                err_sys("open %s error",file);

        for(start_byte = 0; start_byte < 100;start_byte += SIZE_TO_TRY){
                /* construction a flock stucture */
                region_to_test.l_type = F_WRLCK;
                region_to_test.l_whence = SEEK_SET;
                region_to_test.l_start = start_byte;
                region_to_test.l_len = SIZE_TO_TRY;
                region_to_test.l_pid = -1;

                /* show where lock test promot */
                printf("Testing F_WRLCK  on region from %d to %d\n",
                                start_byte,start_byte+SIZE_TO_TRY);

                /* get flock status */
                if(fcntl(fd,F_GETLK,&region_to_test) == -1)
                          err_sys("Error to F_GETLK %s \n",file);
                /* get a lock , show lock status */
                if(region_to_test.l_pid != -1){
                        printf("Lock would fail. F_GETLK returned:\n");
                        show_lock_info(&region_to_test);
                }
                else{
                        printf("F_GETLK - lock would succeed\n");
                }

                /* get a read lock(share lock) */
                region_to_test.l_type = F_RDLCK;
                region_to_test.l_whence = SEEK_SET;
                region_to_test.l_start = start_byte;
                region_to_test.l_len = SIZE_TO_TRY;
                region_to_test.l_pid = -1;

                /* show size get share lock promot */
                printf("Testing F_RDLCK on region from %d to %d\n",
                                start_byte,start_byte+SIZE_TO_TRY);

                /* get share lock flock structure */
                if( (fcntl(fd,F_GETLK,&region_to_test)) == -1)
                        err_sys("Error to get F_GETLK %s\n",file);

                /* get a share lock ,can't set a share lock */
                if(region_to_test.l_pid != -1){
                        printf("Lock would fail, F_GETLK returned:\n");
                        show_lock_info(&region_to_test);
                }
                else{
                        printf("F_RDLCK - lock would succesed\n");
                }
        } /* for */
        close(fd);
        exit(0);
}

void show_lock_info(struct flock *to_show){
        printf("\t l_type %d,  ",to_show->l_type);
        printf("\t l_whence %d,  ",to_show->l_whence);
        printf("\t l_start %d,  ",(int)to_show->l_start);
        printf("\t l_len %d,  ",(int)to_show->l_len);
        printf("\t l_pid %d,  ",to_show->l_pid);
}
