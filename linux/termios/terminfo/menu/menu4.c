#include <term.h>
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <unistd.h>
#include <termios.h>
#include "ourhdr.h"

static  FILE *output_stream = (FILE *)0;

char *menu[] = {
        "a - add new record",
        "q - quit",
        "d - delete record",
        NULL,
};

int getchoice(char *greet, char *choices[], FILE *in, FILE *out);
int char_to_terminal(int char_to_write);
int showInit(int row,int col,char *greet,FILE *out);

int main(){
        int choice;

        do{
                choice = getchoice("Options:",
                                menu,stdin,stdout);
                switch(choice){
                        case  'q':
                                showInit(4,11,"quit process",stdout);
                                break;
                        case  'a':
                                showInit(4,11,"add Cd",stdout);
                                break;
                        case  'd':
                                showInit(4,11,"delete cd",stdout);
                                break;
                }
        }while(!choice);
        exit(0);
}

int getchoice(char *greet, char *choices[], FILE *in, FILE *out){
        int choosen = 0;
        int selected;
        int scrrenrow,scrrentcol = 10;

        char **option;
        char *curses,*clear;

        output_stream = out;
        
        setupterm(NULL,fileno(out),(int *)0);
        curses = tigetstr("cup");
        clear = tigetstr("clear");

        scrrenrow = 4;
        tputs(clear,1,char_to_terminal);
        tputs(tparm(curses,scrrenrow,scrrentcol),1,char_to_terminal);
        fprintf(out,"%s",greet);
        scrrenrow += 2;
        option = choices;
        while(*option){
                tputs(tparm(curses,scrrenrow,scrrentcol),1,char_to_terminal);
                fprintf(out,"%s",*option);
                scrrenrow++;
                option++;
        }
        fprintf(out,"\n");

        tputs(tparm(curses,scrrenrow,scrrentcol),1,char_to_terminal);
        fprintf(out,"You Select:");
        scrrenrow++;

        do{
                fflush(out);

                do{
                selected = fgetc(in);
                }while(selected == '\n');
                fprintf(out,"Current input: %c\n",selected);
                option = choices;
                while(*option){
                        if(selected == *option[0]){
                                choosen = 1;
                                fprintf(out,"choosen seted");
                                break;
                        }
                        option++;
                }
                fprintf(out,"not set");
        }while(!choosen);
        tputs(clear,1,char_to_terminal);
        return selected;
}

int char_to_terminal(int char_to_write){
        if(output_stream)
                putc(char_to_write,output_stream);
        return 0;
}

int showInit(int row,int col,char *greet,FILE *out){
       char *curses,*clear;

       curses = tigetstr("cup");
       clear = tigetstr("clear");

       tputs(tparm(curses,row,col),1,char_to_terminal);
       fprintf(out,"%s\n",greet);
       sleep(2);
       tputs(clear,1,char_to_terminal);
}
