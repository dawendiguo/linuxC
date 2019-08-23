#include <stdlib.h>
#include <stdio.h>
#include <mysql/mysql.h>
#include "ourhdr.h"

MYSQL my_connection;
MYSQL_RES *res_ptr;
MYSQL_ROW sqlrow;

void display_header();
void display_row();

int
main(int argc,char *argv[]){
        int res;
        int first_row = 1;  /* Used to ensure we display the row header exactly once when data is successfully retrieved */

        if(!mysql_init(&my_connection))
                err_sys("mysql_init error");
        if(!mysql_real_connect(&my_connection,"localhost","linux","wj107161","linux",0,NULL,0))
                err_sys("mysql_real_connection error: %s\n",mysql_error(&my_connection));

        printf("Connect success!\n");

        if((res = mysql_query(&my_connection,"SELECT * from data")) != 0)
                err_sys("select * from data error");

        res_ptr = mysql_use_result(&my_connection);
        if(res_ptr){
                while((sqlrow = mysql_fetch_row(res_ptr))){
                        if(first_row){
                                display_header();
                                first_row = 0;
                        }
                        display_row();
                }
                if(mysql_errno(&my_connection))
                        sprintf(stderr,"Retrive error: %s\n",mysql_error(&my_connection));

                mysql_free_result(res_ptr);
        }

        mysql_close(&my_connection);

        return EXIT_SUCCESS;
}

void display_header(){
        MYSQL_FIELD *field_ptr;

        printf("Column datails:\n");
        while((field_ptr = mysql_fetch_field(res_ptr)) != NULL){
                printf("\t Name: %s\n",field_ptr->name);
                printf("\t Type: ");
                if(IS_NUM(field_ptr->type))
                        printf("Numberic field\n");
                else{
                        switch(field_ptr->type){
                                case FIELD_TYPE_VAR_STRING:
                                        printf("VARCHAR\n");
                                        break;
                                case FIELD_TYPE_LONG:
                                        printf("LONG\n");
                                        break;
                                default:
                                        printf("Type is %d, check in mysql_com.h\n",field_ptr->type);
                        } /* switch */
                }   /* else */

                printf("\t Max width %ld\n", field_ptr->length);
                if(field_ptr->flags & AUTO_INCREMENT_FLAG)
                        printf("\t AUTO increments\n");
                printf("\n");
        } /* while */
}

void
display_row(){
        unsigned int field_count;

        field_count = 0;
        while( field_count < mysql_field_count(&my_connection)){
                if(sqlrow[field_count])
                        printf("%s ",sqlrow[field_count]);
                else
                        printf("NULL");
                field_count++;
        }
        printf("\n");
}
