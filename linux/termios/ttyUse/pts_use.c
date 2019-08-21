#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "ourhdr.h"

#define TTY "/dev/tty2"

char *menu[] = {
        "a - add new record",
        "d - delete record",
        "q - quit",
        NULL,
};

int getchoice(char *greet, char *choices[], FILE *in, FILE *out);

int main(void){
        int choice = 0;
        FILE *input;
        FILE *output;

        if(!isatty(fileno(stdout)))
                err_ret("You are not a terminal, OK.\n");

        input = fopen(TTY,"r");
        output = fopen(TTY,"w");

        if(!input || !output)
                err_quit("Unable to open %s\n",TTY);

        do{
                choice = getchoice("Please select an action",menu,input,output);
                printf("You have chosen: %c\n",choice);
        }while(choice != 'q');
        exit(0);
}

int
getchoice(char *greet, char *choices[], FILE *in, FILE *out){
        int chosen = 0;
        int selected;
        char **option;

        do{
                fprintf(out,"Choice: %s\n",greet);
                option = choices;
                while(*option){
                        fprintf(out,"%s\n",*option);
                        option++;
                }
                /* 因为getchar() 每次获取一个字符，如果不用此循环每次getchar()下次获取的就是'\m'。会出现BUG */
                do{
                        selected = getchar();
                }while(selected == '\n');

                option = choices;
                while(*option){
                        if(selected == *option[0]){
                                chosen = 1;
                                break;
                        }
                        option++;
                }

                if(!chosen)
                        fprintf(out,"Incorrect choice, select again\n");
        }while(!chosen);
        return(selected);
}
