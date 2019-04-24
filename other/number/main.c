#include <stdio.h>

int main(){
    int num1 = 11;                      //10进制输入11
    int num2 = 013;                    //8进制输入11
    int num3 = 0xb;                    //16进制输入11 

    printf("num1=%X\n",num1);           //16进制输出
    printf("num2=0%d\n",num2);          //10进制输出
   printf("num3=0x%o\n",num3);          //8进制输出
    if(num1 == num2)                            //判断不同输入方式数字是否相等
        printf("num1 = num2\n");
    if(num1 == num2 && num2 == num3) 
        printf("11 == 013 == 0xb\n");

}
