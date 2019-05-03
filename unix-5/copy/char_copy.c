#include "ourhdr.h"

int main(void){
    char c;

    while( (c = fgetc(stdin)) != EOF){
        if( fputc( c, stdout) == EOF)
            err_sys( "output error" );
    }
    if( ferror(stdin) )
        err_sys("input error");
    
    exit(0);
}
