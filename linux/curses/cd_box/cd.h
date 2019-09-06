#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <curses.h>
#include <string.h>

#define MAX_STRING 80
#define MAX_ENTRY 1024

#define MESSAGE_LINE  6
#define ERROR_LINE  22
#define Q_LINE  20
#define PROMPT_LINE 18

static char current_cd[MAX_STRING] = "\0";
static char current_cat[MAX_STRING];

const char *title_file = "title.cdb";
const char *tracks_file = "tracks.cdb";
const char *temp_file = "cdb.tmp";

void clear_all_screen(void);
void get_return(void);
int get_confirm(void);
int getchoice(char *greet,char *choices[]);
void draw_menu(char *options[],int highligh,
                int start_row,int start_col);
void insert_title(char *cdtitle);
void get_string(char *string);
void add_record(void);
void count_cds(void);
void find_cd(void);
void list_tracks(void);
void remove_tracks(void);
void remove_cd(void);
void update_cd(void);

char *main_menu[] = {
        "add new CD",
        "find CD",
        "count CDs and tracks in the catalog",
        "quit",
        0,
};

char *extended_menu[] = {
        "add new CD",
        "find CD",
        "count CDs and tracks in the catalog",
        "list tracks on current CD",
        "remove current CD",
        "update track information",
        "quit",
        0
};
