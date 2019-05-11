#include "ourhdr.h"
#include <sys/types.h>
#include <sys/acct.h>

#define ACCTFILE "./tmp"
static unsigned long compat2ulong(comp_t);

int main(void){
        struct acct acdata;
        FILE *fp;

        if( ( fp = fopen(ACCTFILE,"r")) == NULL){
                err_sys("fopen error");
        }
        while(fread(&acdata,sizeof(acdata),1,fp) == 1){
                printf("%-*.*s e = %6ld, chars = %7ld stat: %c %c %c %c\n",
                                sizeof(acdata.ac_comm),sizeof(acdata.ac_comm),acdata.ac_comm,
                                compat2ulong(acdata.ac_etime),compat2ulong(acdata.ac_io),
#ifdef  ACORE
                                acdata.ac_flag & ACORE?'D':' ',
#else
                                ' ',
#endif
#ifdef AXSIG
                                acdata.ac_flag & AXSIG?'X':' ',
#else
                                ' ',
#endif
                                acdata.ac_flag & AFORK?'F':' ',
                                acdata.ac_flag & ASU?'S':' '
                                );
        }
        if(ferror(fp))
                err_sys("read error");
        exit(0);
}

static unsigned long 
compat2ulong(comp_t comptime){
        unsigned val;
        int exp;

        val = comptime & 017777;
        exp = (comptime >> 13) & 7;
        while( exp-- > 0)
                val *= 8;
        return(val);
}
