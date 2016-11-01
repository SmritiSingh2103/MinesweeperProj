/* Header files */
#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <menu.h>
#include <string.h>
#include <errno.h>

#define CTRLD	4

typedef struct mine{
char **a;
char **d;
char **e;
int **v;
int k;
}mine;

/* globally declared variables */
int ro = 8, col = 8;        /*.................................default for row and columns is 8 */
int flag1 = 0;      /*........flag1 variable decides whether the game is to be resumed or not */
int dif = 8;/*.............................default for difficulty is 8 i.e no. of mines */
int i,j, x, y;
static int cl = 0, cw = 0; /*Counter for no of games lost and won */

WINDOW *menu, *win, *wins, *win1, *win2, *win3, *win4, *win5, *win7;

/* For printing the menus */ 
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
			"1)The purpose of the game is to open all the ",
			"cells of the board which do not contain a bomb.",
			"2)You lose if you set off a bomb cell. ",
			"3)Every non-bomb cell you open will tell you the ",
			"total number of bombs in the eight neighboring cells.",
			"4)Once you are sure that a cell contains a bomb, ",
			"you can put a flag on it as a reminder.",
			"5)Once you have flagged all the bombs around an open cell",
			"you can quickly open the remaining non-bomb cells.",
		};

char *choices5[] = { 
			"This is a game created by:",
			"Smriti Singh",
			"IT Department",
			"MIS: 111508068",
			"DSA Mini-project 2016-17",

		};

char *choices6[] = { 
			"Resume",
			"Set no. of mines",
			"Stats",
			"Back",

		};


/* Sizes of strings using string pointer */
int n_choices = sizeof(choices) / sizeof(char *);
int n_choices1 = sizeof(choices1) / sizeof(char *);
int n_choices2 = sizeof(choices2) / sizeof(char *);
int n_choices5 = sizeof(choices5) / sizeof(char *);
int n_choices3 = sizeof(choices3) / sizeof(char *);
int n_choices6 = sizeof(choices6) / sizeof(char *);

/* functions to print the menus */
void print_menu(WINDOW *menu, int highlight);
void print_menu1(WINDOW *win, int highlight);
void print_menu2(WINDOW *win1, int highlight);
void print_menu6(WINDOW *win7, int highlight);
void print6(int choice6);
void print3(int choice1);
void stats();

/* Functions to browse through the menus */
void first();
void newer(int choice);
void grid(int ch);
void easy();
void inter();
void diff();
void custom();

/* function to start the game */
void game();
/* function to resume game */
void resume();
/* function to unveil the tile */
int opn(int i, int j, int i1, int j1, int p, int q, mine m);
/* function to reveal all the mines on the minefield when the user clicks on any mine */
void revealmines(mine m, int p, int q);
/* function to save all the data to files */
void save(mine m);
/* function to print the screen with the box and the grid */
void printscr(int x, int y, int p, int q, mine m);
/* function to show the unveiled tile in revealed minefield */
int openmine(int y, int x, int p, int q, mine m);



