#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <gdbm.h>
#include <ndbm.h>
/* On some systems you need to replace the above with 
 * #include <gdbm-ndbm.h>
 */
#include <string.h>
#include "ourhdr.h"

#define TEST_DB_FILE  "/tmp/dbm1.test"
#define ITEMS_USED  3

struct test_data {
        char misc_chars[15];
        int any_integer;
        char more_chars[21];
};

int main(){
        struct test_data items_to_store[ITEMS_USED];
        struct test_data item_retrieved;

        char key_to_use[20];
        int i;

        datum key_datum;
        datum data_datum;

        DBM *dbm_ptr;

        if( (dbm_ptr = dbm_open(TEST_DB_FILE,O_RDWR|O_CREAT,0666)) == NULL)
                err_sys("Failed to open database\n");

        memset(items_to_store,'\0',sizeof(items_to_store));
        strcpy(items_to_store[0].misc_chars,"First");
        items_to_store[0].any_integer = 47;
        strcpy(items_to_store[0].more_chars,"foo");

        strcpy(items_to_store[1].misc_chars,"Second");
        items_to_store[1].any_integer = 13;
        strcpy(items_to_store[1].more_chars,"unlucky");

        strcpy(items_to_store[2].misc_chars,"Third");
        items_to_store[2].any_integer = 3;
        strcpy(items_to_store[2].more_chars,"baz");

        for(i = 0; i < ITEMS_USED; i++){
                sprintf(key_to_use,"%c%c%d",
                                items_to_store[i].misc_chars[0],
                                items_to_store[i].more_chars[0],
                                items_to_store[i].any_integer);
        key_datum.dptr = (void *)key_to_use;
        key_datum.dsize = strlen(key_to_use);
        data_datum.dptr = (void *)&items_to_store[i];
        data_datum.dsize = sizeof(struct test_data);

        if(dbm_store(dbm_ptr,key_datum,data_datum,DBM_REPLACE) != 0)
                err_sys("dbm_store error on key %s\n",key_to_use);
        }

        /* fetch dbm data and printf it */

        /* init fetch key word . type datum */
        sprintf(key_to_use,"Su%d",13);                /* second data */
        key_datum.dptr = key_to_use;
        key_datum.dsize = strlen(key_to_use);


        /* 
         * Other method get data from dbm database */
        
        /* delete a row data from dbm database */
        if(dbm_delete(dbm_ptr,key_datum) != 0)
                err_sys("dbm_delete error for %s\n",key_to_use);
        else
                printf("delete key %s success\n",key_to_use);
        /* show all of dbm data */
        for(key_datum = dbm_firstkey(dbm_ptr);
                        key_datum.dptr;
                        key_datum = dbm_nextkey(dbm_ptr)){
                data_datum = dbm_fetch(dbm_ptr,key_datum);
                if(data_datum.dptr){
                        printf("Data Retrieved\n");
                        memcpy(&item_retrieved,data_datum.dptr,data_datum.dsize);
                        printf("Retrieved item - misc_chars: %s, any_integer : %d, more_chars : %s \n",
                                        item_retrieved.misc_chars,item_retrieved.any_integer,item_retrieved.more_chars);
                }
                else{
                        printf("No data found for key %s\n",key_to_use);
                }
        }
        dbm_close(dbm_ptr);
        exit(0);
}
