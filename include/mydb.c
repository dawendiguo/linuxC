#include "mydb.h"

/* open or create a database. Same arguments sa open(). */
DB *
db_open(const char *pathname, int oflag, int mode){
        DB *db;
        int i,len;
        char asciiptr[PTR_SZ + 1],
             hash[(NHASH_DEF + 1) * PTR_SZ + 2];
             /* +2 for newline and null */
        struct stat statbuff;

        /* Allocate a DB structure, and the buffers it needs */
        len = strlen(pathname);
        if ( ( db = _db_alloc(len)) == NULL)
                err_dump("_db_alloc error for DB");
        db->oflag = oflag;    /* save a copy of the open flags */

        /* Open index file */
        strcpy(db->name,pathname);
        strcat(db->name,".idx");
        if( ( db->idxfd = open(db->name,oflag,mode)) < 0){
                _db_free(db);
                return(NULL);
        }
        
          /* If the database was created, we have to initialize it */
        if( ( oflag & (O_CREAT | O_TRUNC)) == ( O_CREAT | O_TRUNC) ){
                /* Write lock the entire file so that we can stat the file,
                 * check its size, and initialize it, as an atomic operation. */
                if(writew_lock(db->idxfd,0,SEEK_SET,0) < 0)
                        err_dump("writew_lock error");

                if(fstat(db->idxfd,&statbuff) < 0)
                        err_sys("fstat error");
                if(statbuff.st_size == 0){
                        /* We have to build a list of (NHASH_DEF + 1) chain
                         * ptrs with a value of 1. The + 1 is for the free list pointer that precedes the hash table. */
                        sprintf(asciiptr,"%*d",PTR_SZ, 0);
                        hash[0] = 0;
                        for( i = 0; i < (NHASH_DEF + 1) ; i++)
                                strcat(hash,asciiptr);
                        strcat(hash,"\n");

                        i = strlen(hash);
                        if(write(db->idxfd,hash,i) != i)
                                err_dump("write error initializing index file");
                }
                if(un_lock(db->idxfd,0,SEEK_SET,0) < 0)
                        err_dump("un_lock error");
        }
        db->nhash  = NHASH_DEF;
        db->hashoff = HASH_OFF;

        db_rewind(db);

        return(db);
}

/* Allocate a initialize a DB structure to zero */
DB *
_db_alloc(int namelen){
        DB *db;
            /* Use calloc, to init structure to zero */
        if( ( db = maclloc(1,sizeof(DB))) == NULL)
                err_dump("calloc error for DB");

        db->idxfd = db->datfd = -1;

            /* Allocate room for the name.
             * +5 for ".idx" or ".dat" plus null at end */
        if ( (db->name = maclloc(namelen + 5)) == NULL)
                err_dump("maclloc error");

            /* Allocate an index buffer and a data buffer.
             * +2 for newline and null at end. */
        if( ( db->idxbuf = maclloc(IDXLEN_MAX + 2)) == NULL)
                err_dump("malloc error for index buffer");
        if((db->datbuf = maclloc(DATLEN_MAX + 2)) == NULL)
                err_dump("malloc error for data buffer");

        return(db);
}

/* Free up a DB structure. and all the malloc'ed buffers it
 * may point to. Aleo close the file descriptors if still open*/
int
_db_free(DB *db){
        if(db->idxfd >= 0 && close(db->idxfd) < 0)
                err_dump("index close error");
        if(db->datfd >= 0 && close(db->datfd) < 0)
                err_dump("data close error");
        db->idxfd = db->datfd = -1;

        if(db->idxbuf != NULL)
                free(db->idxbuf);
        if(db->datbuf != NULL)
                free(db->datbuf);
        if(db->name != NULL)
                free(db->name);
        free(db);
        return(0);
}

void
db_close(DB *db){
        _db_free(db);
}

/* Fetch a specified record.
 * We return a pointer to the null-terminated data. */
char *
db_fetch(DB *db, const char *key){
        char *ptr;

        if(_db_find(db,key,0) < 0){
                ptr = NULL;
                db->cnt_fetcherr++;
        }
        else{
                ptr = _db_readdat(db);
                db->cnt_fetcherr++;
        }

              /* Unlock the hash chain that _db_find() locked */
        if(un_lock(db->idxfd,db->chainoff,SEEK_SET,1) < 0)
                err_dump("un_lock error");
        return(ptr);
}

/* Find the specified record.
 * Called by db_delete(), db_fetch(), and db_store(). */
int _db_find(DB *db, const char *key, int writelock){
        off_t offset,nextoffset;

            /* Calculate hash value for this key, then calculate byte
             * offset of corresponding chan ptr in hash table.
             * This is where our search starts. */
            /* calc offset in hash table for this key */
        db->chainoff = (_db_hash(db,key) * PTR_SZ) + db->hashoff;
        db->ptroff = db->chainoff;
            /* Here's where we lock this hash chain. It's the caller's responsibility to unlock it when done.
             * Note we lock and punlock only the first byte. */
        if(writelock){
                if(writew_lock(db->idxfd,db->chainoff,SEEK_SET,1) < 0)
                        err_dump("writew_lock error");
        }
        else{
                if(readw_lock(db->idxfd,db->chainoff,SEEK_SET,1) < 0)
                        err_dump("readw_lock error");
        }

            /* Get the offset in the index file or first record 
             * on the hash chain (can be 0) */
        offset = _db_readptr(db,db->ptroff);

        while(offset != 0){
                nextoffset = _db_readidx(db,offset);
                if(strcmp(db->idxbuf,key) == 0)
                        break;

                db->ptroff = offset;      /* offset of this (unequal) record */
                offset = nextoffset;      /* next one to compare */
        }
        if(offset == 0)
                return(-1);     /* error, record not found */

        /* We have a match. We're quaranteed that db->ptroff contains 
         * the offset of the chain ptr that points to this matching 
         * index record. _db_dodelete() uses this fact. ( The chain
         * ptr that points to this matching record could be in an 
         * index record or in the hash table.) */
        return(0);
}
