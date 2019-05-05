#include "ourhdr.h"

//显示变量值
static void showVar(char *);
//自定义字符串相加
static void my_strcat(char *,char *);

int main(void){
    char *str;
    //第一个变量名
    char *name = "MY_Test";
    //另外一个变量名字
    char *env = "Other_test";

    str = (char *)malloc(8);
    strcpy(str,name);
    //显示环境变量PATH的值
    showVar("PATH");

    //测试显示第一个变量值
    showVar(name);
    //设置第一个自定义环境变量
    /* Input 
     * KEY=VALUE  中间不能有空格
     * 这里用法自定义字符串相加函数
     * Return char * 字符串
     */
    //putenv 成功返回0,否则返回非0
    if(realloc(str,strlen(str)+strlen("=my first name")+1) == NULL){
            err_sys("realloc error");
    }
    strcat(str,"=my first name");
    printf("put envriment String: %s\n",str);
    if(putenv(str) != 0)
        err_sys("putenv error");

    //再次确认设置自定义变量结果
    showVar(name);

    //测试自定义变量2
    showVar(env);
    //用setenv设置自定义变量值
    //int setenv(char *KEY,char *VALUE,int Overwrite)
    //成功返回0.否则非0
    if(setenv(env,"just other test",1) != 0)
    err_sys("setenv error");

    //确认
    showVar(env);

    return(0);
}

static void showVar(char n[]){
    char *output;
    
    if( (output = getenv(n)) == NULL)
        printf("Don't set %s\n",n);
    else
        printf("%s = %s \n",n,output);
}

/*two string add
static void my_strcat(char *str1,char *str2){
    //扩大str1
    if(realloc(str1,(strlen(str1)+strlen(str2)+1)) == NULL)
         err_sys("realloc error");

    //连接临时返回字符串和str2
    strcat(str1,str2);
}*/
