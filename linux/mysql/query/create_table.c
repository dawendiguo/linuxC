#include <stdlib.h>
#include <stdio.h>
#include "ourhdr.h"
#include <mysql/mysql.h>

#define CREATE_TABLE  "CREATE table test \
        (id int primary key auto_increment not null,\
         testid int not null);"

int main(int argc,char *argv[]){
        MYSQL conn_ptr;

        mysql_init(&conn_ptr);

        if(mysql_real_connect(&conn_ptr,"localhost","linux","wj107161","linux",0,NULL,0)){
                if(mysql_query(&conn_ptr,CREATE_TABLE) == 0)
                        printf("create table test success\n");
                else
                        err_quit("create table test error");
                if(mysql_query(&conn_ptr,"drop table test") == 0)
                        printf("drop table test success\n");
                else
                        err_quit("drop table test failed");
        }
}
