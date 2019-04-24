#include <stdio.h>
#include "ourhdr.h"

void print_bin(int);
int main(){
    int num= 9;

    //printf(" %d binary :",num);
    print_bin(num);
   printf("\n");
}


void print_bin(int n){
    int l = sizeof(n)*8;            //总位数
    int i;
    if( n == 0){                        //判断输入是否为0
        printf("0");
        return ;
    }

    for( i = l -1 ; i >= 0; i--){           //跳过前面为0的位
        if(n&(1<<i)) break;             //这里有个与运算&和位运算<<  1<<i 就是把第1这个数字在内存中左移i位
    }
    for(;i>=0;i--){                             //上一个循环找到了第一个不为0的位，输出从这里开始
        printf("%d",(n&(1<<i)) != 0);
    }
}
