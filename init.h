#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <locale.h>

int width = 0, height = 0;
int mine_ratio = 10, n_mines;
int reveal = 0;
int i,j, x, y;

WINDOW *winn, *wrap;
WINDOW *menu_win, *win, *win1, *win2, *win3, *win4, *win5;

char *choices[] = { 
			"Game",
			"Options",
			"Help",
			"Exit",
		  };


char *choices1[] = { 
			"Easy",
			"Intermediate",
			"Difficult",
			"Custom",
			"Back",
		  };

char *choices2[] = { 
			"Instructions",
			"About",
			"Back",
		   };

char *choices3[] = { 
			"Instructions for Minesweeper:",
			"    ",
			"1) Click on the block you want to open",
			"2) If a number appears on it, it has that many ",
			"mines around the block",
			"3)Right click to mark the block you think contains the bomb",
			"4)Open all the blocks without mines to win"

		};

char *choices5[] = { 
			"This is a game created by:",
			"Smriti Singh",
			"IT Department",
			"MIS: 111508068",
			"DSA Mini-project 2016-17",

		};


int n_choices = sizeof(choices) / sizeof(char *);
void print_menu(WINDOW *menu_win, int highlight);

int n_choices1 = sizeof(choices1) / sizeof(char *);
void print_menu1(WINDOW *win, int highlight);

int n_choices2 = sizeof(choices2) / sizeof(char *);
void print_menu2(WINDOW *win1, int highlight);

int n_choices5 = sizeof(choices5) / sizeof(char *);
int n_choices3 = sizeof(choices3) / sizeof(char *);

void newer(int choice);
void print3(int choice1);
void first();
void grid(int ch);
void init_mines(void * ptr);
int mine_clear(void *ptr, int x, int y, int mass_clear);
void mine_mark(void *ptr, int x, int y);
int check_wining(void *ptr);
void repaint(void *ptr);
void easy();
void inter();
void diff();
void custom();


enum {
	M_NONE = 0,
	M_CLEARED = 1 << 0,
	M_MARKED  = 1 << 1,
	M_MINED   = 1 << 2,
	M_BOMBED  = 1 << 3,
};

typedef struct { unsigned short flag, cnt; } mine_t;
