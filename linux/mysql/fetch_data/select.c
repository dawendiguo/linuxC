#include <stdlib.h>
#include <stdio.h>
#include <mysql/mysql.h>
#include "ourhdr.h"

MYSQL my_connection;
MYSQL_RES *res_ptr;
MYSQL_ROW sqlrow;

int
main(int argc,char *argv[]){
        int res;

        mysql_init(&my_connection);

        if(!mysql_real_connect(&my_connection,"localhost","linux","wj107161","linux",0,NULL,0))
                err_quit("mysql connect error: %s",mysql_error(&my_connection));
        else
                printf("Connect database Success\n");

        if((res = mysql_query(&my_connection,"SELECT name,password FROM data")) != 0)
                err_sys("mysql query error");

        res_ptr = mysql_store_result(&my_connection);                     // get result

        if(res_ptr){
                printf("Retrived %lu rows\n",(unsigned long)mysql_num_rows(res_ptr));
                while((sqlrow = mysql_fetch_row(res_ptr)))
                        printf("Fetched - name: %s, password: %s\n",sqlrow[0],sqlrow[1]);

                if(mysql_errno(&my_connection))
                        err_quit("Retrive error: %s\n",mysql_error(&my_connection));

                mysql_free_result(res_ptr);
        }

        mysql_close(&my_connection);
        return(EXIT_SUCCESS);
}
