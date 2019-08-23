#include <stdlib.h>
#include <stdio.h>
#include "ourhdr.h"
#include <mysql/mysql.h>

int
main(int argc,char *argv[]){
        MYSQL *conn_ptr;

        conn_ptr = mysql_init(NULL);

        if(!conn_ptr)
                err_quit("mysql_init error");

        conn_ptr = mysql_real_connect(conn_ptr,"localhost","linux","wj107161","linux",0,NULL,0);

        if(conn_ptr)
                printf("Connection success\n");
        else
                printf("Connection failed\n");
        mysql_close(conn_ptr);
        
        return EXIT_SUCCESS;
}
