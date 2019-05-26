#include <setjmp.h>
#include "ourhdr.h"

static jmp_buf jmpBuf;

static void test(){
        //jump to setjump , return 3
        longjmp(jmpBuf,3);
}

int main(void){
        int jmpNum;

        //init jmp_buf ok
        if((jmpNum = setjmp(jmpBuf)) == 0){
                printf("init setjmp ok!\n");
                test();
                pause();
        }
        /*longjmp return 3*/
        else{
              printf("longjmp return value:%d\n",jmpNum);
        }
        exit(0);
}
