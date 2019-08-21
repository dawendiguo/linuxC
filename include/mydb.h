#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stddef.h>
#include "ourhdr.h"

              /* flags for db_stor() */
#define DB_INSERT   1               /* insert new record only */
#define DB_REPLACE  2               /* replace existing record */

              /* magic numbers */
#define IDXLEN_SZ     4             /* #asii chars for length of index record */
#define IDXLEN_MIN    6             /* key,sep,start,sep,length,newline */
#define IDXLEN_MAX    1024          /* arbitray */
#define SEP           ':'           /* separator chracter in index record */
#define DATLEN_MIN    2             /* data bye, newline */
#define DATLEN_MAX    1024          /* arbitray */

            /* following definitions are for bash chains and free list chain in index file */
#define PTR_SZ        6             /* size fo ptr field in hash chain */
#define PTR_MAX       999999        /* max offset (file size) = 10**PTR_SZ - 1 */
#define NHASH_DEF     137           /* default hash table size */
#define FREE_OFF      0             /* offset of ptr to free list in index file */
#define HASH_OFF      PTR_SZ        /* offset of bash table in index file */

typedef struct {            /* our internal structure */
          int idxfd;        /* fd for index file */
          int datfd;        /* fd for data file */
          int oflag;        /* flags for open()/db_open(): o_xxx */

          char *idxbuf;     /* malloc'ed buffer for index record */
          char *datbuf;     /* malloc'ed buffer for data record */
          char *name;       /* name db was opened under */
          off_t idxoff;     /* offset in index file of index record */
                            /* actual dey is st (idxoff + PTR_SZ + IDXLEN_SZ) */
          size_t idxlen;    /* length of index record 
                               excludes IDXLEN_SZ bytes at front of index record
                               includes newline at end of index record */
          off_t dataoff;    /* offset in data file of data record */
          size_t datlen;    /* lenght of data record 
                               includes newline at end */
          off_t ptrval;     /* contents of chain ptr in index record */
          off_t ptroff;     /* offset of chain ptr that points to this index record */
          off_t chainoff;   /* offset of hash chain for this index record */
          off_t hashoff;    /* offset in index file of hash table */
          int nhash;        /* current hash table size*/
          long cnt_delok;   /* delete OK */
          long cnt_delerr;  /* delete error */
          long cnt_fetchok; /* fetch OK */
          long cnt_fetcherr;/* fetch error */
          long cnt_nexrec;  /* next record */
          long cnt_stor1;   /* store: DB_INSERT, no empty, appended */
          long cnt_stor2;   /* store: DB_INSERT, found empty, reused */
          long cnt_stor3;   /* store: DB_REPLACE, deff data len, appended */
          long cnt_stor4;   /* store: DB_REPLACE, same data len, overwrote */
          long cnt_storerr; /* store error */
}DB;
typedef unsigned long hash_t;   /* hash values */
          /* user_callable functons */
DB  *db_open(const char *,int,int);
void db_close(DB *);
char *db_fetch(DB *,const char *);
int db_store(DB *, const char *, const char *, int);
int db_delete(DB *, const char *);
void db_rewind(DB *);
char *db_nextrec(DB *, char *);
void db_state(DB *);
          /* internal functions */
DB  *_db_alloc(int);
int  _db_checkfree(DB *);
int _db_dodelete(DB *);
int _db_emptykey(char *);
int _db_find(DB *, const char *, int);
int _db_findfree(DB *, int, int);
int _db_free(DB *);
hash_t _db_hash(DB *, const char *);
char *_db_nextdey(DB *);
char *_db_readdat(DB *);
off_t _db_readidx(DB *, off_t);

off_t _db_readptr(DB *, off_t);
void _db_writedat(DB *, const char *, off_t, int);
void _db_writeidx(DB *, const char *, off_t, int, off_t);
void _db_writeptr(DB *, off_t, off_t);
