#include <unistd.h>
#include <curses.h>
#include <stdlib.h>

#define LOCAL_ESCAPE_KEY 27

int main(){
        int key;

        initscr();

        cbreak();
        keypad(stdscr,TRUE);
        noecho();
        clear();
        mvprintw(5,5,"Key pad demonstration. Press 'q' to quit");
        move(7,5);
        refresh();
        key = getch();
        
        while(key != ERR && key != 'q'){
                move(7,5);
                clrtoeol();

                attron(A_BOLD);
                if((key >= 'A' && key <= 'Z') ||
                   (key >= 'a' && key <= 'z'))
                        printw("You press char key: %c",(char)key);
                else if( key >= '0' &&  key <= '9')
                        printw("You press number key: %d",(int)key - 48);
                else{
                        switch(key){
                                case LOCAL_ESCAPE_KEY: printw("%s","Escape key"); break;
                                case KEY_END: printw("%s","End key"); break;
                                case KEY_BEG: printw("%s","BEGINNING KEY"); break;
                                case KEY_RIGHT: printw("%s","RIGHT KEY"); break;
                                case KEY_LEFT:  printw("%s","LEFT KEY");  break;
                                case KEY_UP:  printw("%s","UP KEY"); break;
                                case KEY_DOWN:  printw("%s","DOWN KEY");  break;
                                case KEY_F(1):  printw("%s"," You Press F1"); break;
                                case KEY_F(2):  printw("%s","You Press F2"); break;
                                default: printw("Unmatched - %d",key); break;
                        } /* switch */
                } /* else */
        attroff(A_BOLD);
        refresh();
        key = getch();
        } /* while */


        endwin();
        exit(0);
}
