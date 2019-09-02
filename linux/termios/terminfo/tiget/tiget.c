#include <stdio.h>
#include <stdlib.h>
#include <term.h>
#include <curses.h>

int main(){
        int nrows,ncolumns;
        char *ncup;

        setupterm("linux",fileno(stdout),(int *)0);
        nrows = tigetnum("lines");
        ncolumns = tigetnum("cols");
        ncup = tigetstr("cup");
        printf("This termios has %d columns and %d rows \n",ncolumns,nrows);
        printf("This termios has cup: %s\n",ncup);
        exit(0);
}
