#include "ourhdr.h"
#include "myttyname.c"

int main(void){
        printf("fd 0: %s\n",isatty(0)?myttyname(0):"not a tty");
        printf("fd 1: %s\n",isatty(1)?myttyname(1):"not a tty");
        printf("fd 2: %s\n",isatty(2)?myttyname(2):"not a tty");
}
