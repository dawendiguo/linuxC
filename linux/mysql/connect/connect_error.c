#include <stdio.h>
#include <stdlib.h>
#include "ourhdr.h"
#include <mysql/mysql.h>

int
main(int argc,char *argv[]){
        MYSQL my_connection;
        
        mysql_init(&my_connection);
        if(mysql_real_connect(&my_connection,"localhost","linux","errorPassword","linux",0,NULL,0))
                printf("connect success\n");
        else
                err_quit("connect failed");
        return(EXIT_SUCCESS);
}
