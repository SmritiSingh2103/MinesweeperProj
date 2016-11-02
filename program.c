/*****************************************************************************
* Copyright (C) Smriti Singh smritisingh2103@gmail.com
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation; either version 2.1 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this program; if not, write to the Free Software Foundation,
* Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
*****************************************************************************/

#include "init.h"

int main ()
{

  first ();
  return 0;

}

void resume ()
{

/* clearing everything before starting the game */
  clear ();

/* Variable declarations */
  int i, j, y, x, p, q, i1 = 0, i2, j2, mines = 0;
  int c;
  char b;
  char str[4];

/* Initial conditions */
  initscr ();
  cbreak ();
  noecho ();

/* Switching keyboard interface on */
  keypad (stdscr, TRUE);

/* Setting the background colour of the window */
  start_color ();
  init_pair (1, COLOR_BLACK, COLOR_YELLOW);
  attrset (COLOR_PAIR (1));

/* Setting a box around the window */
  box (stdscr, 0, 0);

/* printing the instructions on the top */
  mvprintw (1, 1, "Use Arrow Keys To Navigate");
  mvprintw (2, 1, "Press Enter To Select Tile");
  mvprintw (3, 1, "Press Q To Exit");
  mvprintw (4, 1, "Press F To Flag");
 
/* declaring variable of datatype mine */
  mine m;

      FILE *gp;
      gp = fopen ("resume1.txt", "r");
      if (gp == NULL){
	  system("clear");
	  erase();
	  refresh();
	  mvprintw (6, 6,
	    "No game available to resume");
          refresh ();
          sleep(2);
          first();
	 }

/* reading data from the saved file */
      fscanf (gp, "%d", &(m.k));
      fscanf (gp, "%d", &ro);
      fscanf (gp, "%d", &col);
      fscanf (gp, "%d", &dif);
      fclose (gp);
    

/* allocating memory to every element of the datatype mine */
  m.v = (int **) malloc (sizeof (int *) * ro);
  for (i = 0; i < ro; i++)
    m.v[i] = (int *) malloc (sizeof (int) * col);
  m.a = (char **) malloc (sizeof (char *) * ro);
  for (i = 0; i < ro; i++)
    m.a[i] = (char *) malloc (sizeof (char *) * col);
  m.d = (char **) malloc (sizeof (char *) * ro);
  for (i = 0; i < ro; i++)
    m.d[i] = (char *) malloc (sizeof (char *) * col);
  m.e = (char **) malloc (sizeof (char *) * ro);
  for (i = 0; i < ro; i++)
    m.e[i] = (char *) malloc (sizeof (char *) * col);

 /* reading data from the saved file */
      FILE *fp;
      char z;
      fp = fopen ("resume.txt", "r");
      if (fp == NULL){
	  system("clear");
	  erase();
	  refresh();
	  mvprintw (12, 12,
	    "No game available to resume");
          refresh ();
          sleep(2);
          first();
	 }
      for (i = 0; i < ro; i++){
	  for (j = 0; j < col; j++)
	    fscanf (fp, "%c", &(m.a[i][j]));
	}
      for (i = 0; i < ro; i++){
	  for (j = 0; j < col; j++)
	    fscanf (fp, "%c", &(m.d[i][j]));
	}
      for (i = 0; i < ro; i++){
	  for (j = 0; j < col; j++)
	    fscanf (fp, "%c", &(m.e[i][j]));
	}
      for (i = 0; i < ro; i++){
	  for (j = 0; j < col; j++){
	      fscanf (fp, "%c", &z);
	      i2 = atoi (&z);
	      m.v[i][j] = i2;
	    }
	}
      fclose (fp);
        
 mvprintw ((LINES - ro - 20) / 2, (COLS - 14) / 2, "Mines left: %d",
	    (dif - m.k));

/*printing the minefield in the middle*/
  x = (COLS - ((col - 1) * 4 + 1)) / 2;
  p = x;
  y = (LINES - (ro - 1) * 2) / 2;
  q = y;
  move (y, x);
  printscr (x, y, p, q, m);
  move (q, p);
  x = p;
  y = q;

/*assigning functions to keys till the key q is pressed */
  while ((c = getch ()) != 'q') {
      int flag = 0;
      switch (c){
	case KEY_UP:
	  if (y == q)
	    y = q + (ro - 1) * 2;
	  else
	    y -= 2;
	  break;
	case KEY_DOWN:
	  if (y == q + (ro - 1) * 2)
	    y = q;
	  else
	    y += 2;
	  break;
	case KEY_RIGHT:
	  if (x == p + (col - 1) * 4)
	    x = p;
	  else
	    x += 4;
	  break;
	case KEY_LEFT:
	  if (x == p)
	    x = p + (col - 1) * 4;
	  else
	    x -= 4;
	  break;
/* for displaying the complete minefield when the cheat code "cheat" is pressed */
	case 'c':
	  getstr (str);
	  if (strcmp (str, "heat") == 0){
/* displays the mine in the center right corner */
	      for (i = 0; i < ro; i++){
		  for (j = 0; j < col; j++)
		    mvprintw ((LINES - ro) / 2 + i, COLS - col + j, "%c",
			      m.a[i][j]);
		  mvprintw ((LINES - ro) / 2 + i, COLS - col + j, "\n");
		}
	    }
	  break;
/* for unveiling the mine when enter is pressed */
	case 10:
/* does not unveil the tile if there is a mine or it is flagged already */
	  if (m.a[(y - q) / 2][(x - p) / 4] == '*'
	      && m.d[(y - q) / 2][(x - p) / 4] != '#'){
	      revealmines (m, p, q);
	      attron (COLOR_PAIR (1));
	      refresh ();
	      sleep (1);

/* diplaying the end of game */
	      mvprintw ((LINES) / 2, (COLS - 16) / 2, "BOOM!!! YOU LOST");
	      attroff (COLOR_PAIR (1));
	      cl++;
	      remove("resume1.txt");
	      remove("resume.txt");
	      refresh ();
	      sleep (2);
	      dif = 8;
	      ro = 8;
	      col = 8;
	      return;
	    }

/* do nothing if it is a flagged tile */
	  else if (m.d[(y - q) / 2][(x - p) / 4] == '#');

/* unveil the tile if the above conditions are false */
	  else if (m.a[(y - q) / 2][(x - p) / 4] != '*'){
	      printw ("%c", m.a[(y - q) / 2][(x - p) / 4]);
	      m.e[(y - q) / 2][(x - p) / 4] = m.a[(y - q) / 2][(x - p) / 4];
	      if (m.a[(y - q) / 2][(x - p) / 4] == ' '){
		  move (y, x);
		  openmine (y, x, p, q, m);
		}
	    }
	  break;
/* for marking the mine as flagged */
	case 'f':
	  if (m.e[(y - q) / 2][(x - p) / 4] == '.') {
	      printw ("#");
	      m.e[(y - q) / 2][(x - p) / 4] = '#';

/* k is the counter for the no. of tiles that are flagged */
	      m.k++;
	      m.d[(y - q) / 2][(x - p) / 4] = '#';
	    }

/* unflag the flagged tile */
	  else if (m.e[(y - q) / 2][(x - p) / 4] == '#'){
	      m.e[(y - q) / 2][(x - p) / 4] = '.';
	      m.d[(y - q) / 2][(x - p) / 4] = '3';
	      printw (".");

/* decrease the count */
	      m.k--;
	    }

/* printing the no. of mines left */
	  mvprintw ((LINES - ro - 20) / 2, (COLS - 14) / 2, "Mines left: %d",
		    (dif - m.k));
	  if ((dif - m.k) < 10 && (dif - m.k) >= 0)
	    mvprintw ((LINES - ro - 20) / 2, (COLS - 14) / 2 + 13, " ");
	  break;
	}

/* checking if the tiles flagged are actually mines */
      if (m.k == dif){
	  for (i = 0; i < ro; i++) {
	      for (j = 0; j < col; j++){
		  if ((m.a[i][j] != '*' && m.d[i][j] == '3')
		      || (m.a[i][j] == '*' && m.d[i][j] == '#'))
		    flag++;
		}
	    }
	}
      refresh ();

      if (flag == (ro * col)){
	  attron (COLOR_PAIR (1));
	  refresh ();
	  sleep (1);
	  mvprintw ((LINES) / 2, (COLS - 20) / 2, "CONGRATS!!! YOU WIN");
	  attroff (COLOR_PAIR (1));
	  cw++;

/* Removing saved files */
	  remove("resume.txt");
	  remove("resume1.txt");

	  refresh ();
	  sleep (3);
	  dif = 8;
	  ro = 8;
	  col = 8;
	  return;
	}
      move (y, x);
    }

  flag1 = 0;

/* before quitting the game pop up appears */
  mvprintw (LINES / 2, (COLS - 28) / 2, "Do You Want To Save The Game");
  mvprintw (LINES / 2 + 1, COLS / 2 - 3, "(y/n)?");

  while (1){

/* if y is pressed */
      if ((c = getch ()) == 'y')
	{
	  save (m);
	  first ();
	  break;
	}

/* if n is pressed */
      else if (c == 'n')
	{
	  refresh();
	  first();
	  break;
	}
    }

/* free all the elements */
  for (i = 0; i < ro; i++)
    free (m.v[i]);
  free (m.v);
  for (i = 0; i < ro; i++)
    free (m.a[i]);
  free (m.a);
  for (i = 0; i < ro; i++)
    free (m.d[i]);
  free (m.d);
  for (i = 0; i < ro; i++)
    free (m.e[i]);
  free (m.e);
  refresh ();
  clear ();
  refresh ();

/* resetting everything to default */
  dif = 8;
  ro = 8;
  col = 8;
}

void game ()
{

/* clearing everything before starting the game */
  clear ();

/* Variable declarations */
  int i, j, y, x, p, q, i1 = 0, i2, j2, mines = 0;
  int c;
  char b;
  char str[4];

/* Initial conditions */
  initscr ();
  cbreak ();
  noecho ();

/* Switching keyboard interface on */
  keypad (stdscr, TRUE);

/* Setting the background colour of the window */
  start_color ();
  init_pair (1, COLOR_BLACK, COLOR_YELLOW);
  attrset (COLOR_PAIR (1));

/* Setting a box around the window */
  box (stdscr, 0, 0);

/* printing the instructions on the top */
  mvprintw (1, 1, "Use Arrow Keys To Navigate");
  mvprintw (2, 1, "Press Enter To Select Tile");
  mvprintw (3, 1, "Press Q To Exit");
  mvprintw (4, 1, "Press F To Flag");
  mvprintw (5, 1, "Press N For New Game");

/* declaring variable of datatype mine */
  mine m;

/* allocating memory to every element of the datatype mine */
  m.v = (int **) malloc (sizeof (int *) * ro);
  for (i = 0; i < ro; i++)
    m.v[i] = (int *) malloc (sizeof (int) * col);
  m.a = (char **) malloc (sizeof (char *) * ro);
  for (i = 0; i < ro; i++)
    m.a[i] = (char *) malloc (sizeof (char *) * col);
  m.d = (char **) malloc (sizeof (char *) * ro);
  for (i = 0; i < ro; i++)
    m.d[i] = (char *) malloc (sizeof (char *) * col);
  m.e = (char **) malloc (sizeof (char *) * ro);
  for (i = 0; i < ro; i++)
    m.e[i] = (char *) malloc (sizeof (char *) * col);
  
  if(flag1 == 1)
     resume();
  if (flag1 == 0){
/* initialising each element of the mine */
      m.k = 0;

      for (i = 0; i < ro; i++){
	  for (j = 0; j < col; j++)
	    m.v[i][j] = 0;
	}
      for (i = 0; i < ro; i++){
	  for (j = 0; j < col; j++)
	    m.a[i][j] = 'q';
	}
      for (i = 0; i < ro; i++){
	  for (j = 0; j < col; j++)
	    m.d[i][j] = '3';
	}

/* making the minefield using the function rand */
      srand (time (NULL));
      while (i1 < dif){
	  i2 = rand () % ro;
	  j2 = rand () % col;
	  while (m.a[i2][j2] != '*'){
	      m.a[i2][j2] = '*';
	      i1++;
	    }
	}
      for (i = 0; i < ro; i++){
	  for (j = 0; j < col; j++)
	    m.e[i][j] = '.';
	}
/*counting the no. of mines around each box*/
      for (i2 = 0; i2 < ro; i2++){
	  for (j2 = 0; j2 < col; j2++){
	      mines = 0;
	      for (i = -1; i <= 1; i++){
		  for (j = -1; j <= 1; j++){
		      if (((i2 + i) < 0) || ((i2 + i) > (ro - 1))
			  || ((j2 + j) < 0) || ((j2 + j) > (col - 1)))
			mines = mines + 0;
		      else if (m.a[i2 + i][j2 + j] != '*')
			mines = mines + 0;
		      else if (m.a[i2 + i][j2 + j] == '*')
			mines = mines + 1;
		    }
		}

/* 48 is ascii of 0 */
	      b = mines + 48;
	      if (b == 48)
		m.a[i2][j2] = ' ';
	      if (m.a[i2][j2] != '*' && m.a[i2][j2] != ' ')
		m.a[i2][j2] = b;
	    }
	}
    }

  mvprintw ((LINES - ro - 20) / 2, (COLS - 14) / 2, "Mines left: %d",
	    (dif - m.k));

/*printing the minefield in the middle*/
  x = (COLS - ((col - 1) * 4 + 1)) / 2;
  p = x;
  y = (LINES - (ro - 1) * 2) / 2;
  q = y;
  move (y, x);
  printscr (x, y, p, q, m);
  move (q, p);
  x = p;
  y = q;

/*assigning functions to keys till the key q is pressed */
  while ((c = getch ()) != 'q') {
      int flag = 0;
      switch (c){
	case KEY_UP:
	  if (y == q)
	    y = q + (ro - 1) * 2;
	  else
	    y -= 2;
	  break;
	case KEY_DOWN:
	  if (y == q + (ro - 1) * 2)
	    y = q;
	  else
	    y += 2;
	  break;
	case KEY_RIGHT:
	  if (x == p + (col - 1) * 4)
	    x = p;
	  else
	    x += 4;
	  break;
	case KEY_LEFT:
	  if (x == p)
	    x = p + (col - 1) * 4;
	  else
	    x -= 4;
	  break;
/* for displaying the complete minefield when the cheat code "cheat" is pressed */
	case 'c':
	  getstr (str);
	  if (strcmp (str, "heat") == 0){
/* displays the mine in the center right corner */
	      for (i = 0; i < ro; i++){
		  for (j = 0; j < col; j++)
		    mvprintw ((LINES - ro) / 2 + i, COLS - col + j, "%c",
			      m.a[i][j]);
		  mvprintw ((LINES - ro) / 2 + i, COLS - col + j, "\n");
		}
	    }
	  break;
/* for unveiling the mine when enter is pressed */
	case 10:
/* does not unveil the tile if there is a mine or it is flagged already */
	  if (m.a[(y - q) / 2][(x - p) / 4] == '*'
	      && m.d[(y - q) / 2][(x - p) / 4] != '#'){
	      revealmines (m, p, q);
	      attron (COLOR_PAIR (1));
	      refresh ();
	      sleep (1);

/* diplaying the end of game */
	      mvprintw ((LINES) / 2, (COLS - 16) / 2, "BOOM!!! YOU LOST");
	      attroff (COLOR_PAIR (1));
	      cl++;
	      refresh ();
	      sleep (2);
	      dif = 8;
	      ro = 8;
	      col = 8;
	      return;
	    }

/* do nothing if it is a flagged tile */
	  else if (m.d[(y - q) / 2][(x - p) / 4] == '#');

/* unveil the tile if the above conditions are false */
	  else if (m.a[(y - q) / 2][(x - p) / 4] != '*'){
	      printw ("%c", m.a[(y - q) / 2][(x - p) / 4]);
	      m.e[(y - q) / 2][(x - p) / 4] = m.a[(y - q) / 2][(x - p) / 4];
	      if (m.a[(y - q) / 2][(x - p) / 4] == ' '){
		  move (y, x);
		  openmine (y, x, p, q, m);
		}
	    }
	  break;
/* for starting a new game when n is pressed */
	case 'n':
	  mvprintw (LINES / 2, (COLS - 25) / 2,
		    "Do Want To Start A New Game");
	  mvprintw (LINES / 2 + 1, COLS / 2 - 3, "(y/n)?");

/* if the user presses y */
	  if ((c = getch ()) == 'y') {
	      clear ();
	      refresh ();
	      endwin ();
	      game();
	     }

/* if the user presses n */
	  else if (c == 'n') {
	      clear ();
	      refresh ();
	      flag1 = 1;
	      save (m);
	      game();
	    }
	  break;

/* for marking the mine as flagged */
	case 'f':
	  if (m.e[(y - q) / 2][(x - p) / 4] == '.') {
	      printw ("#");
	      m.e[(y - q) / 2][(x - p) / 4] = '#';

/* k is the counter for the no. of tiles that are flagged */
	      m.k++;
	      m.d[(y - q) / 2][(x - p) / 4] = '#';
	    }

/* unflag the flagged tile */
	  else if (m.e[(y - q) / 2][(x - p) / 4] == '#'){
	      m.e[(y - q) / 2][(x - p) / 4] = '.';
	      m.d[(y - q) / 2][(x - p) / 4] = '3';
	      printw (".");

/* decrease the count */
	      m.k--;
	    }

/* printing the no. of mines left */
	  mvprintw ((LINES - ro - 20) / 2, (COLS - 14) / 2, "Mines left: %d",
		    (dif - m.k));
	  if ((dif - m.k) < 10 && (dif - m.k) >= 0)
	    mvprintw ((LINES - ro - 20) / 2, (COLS - 14) / 2 + 13, " ");
	  break;
	}

/* checking if the tiles flagged are actually mines */
      if (m.k == dif){
	  for (i = 0; i < ro; i++) {
	      for (j = 0; j < col; j++){
		  if ((m.a[i][j] != '*' && m.d[i][j] == '3')
		      || (m.a[i][j] == '*' && m.d[i][j] == '#'))
		    flag++;
		}
	    }
	}
      refresh ();

      if (flag == (ro * col)){
	  attron (COLOR_PAIR (1));
	  refresh ();
	  sleep (1);
	  mvprintw ((LINES) / 2, (COLS - 20) / 2, "CONGRATS!!! YOU WIN");
	  attroff (COLOR_PAIR (1));
	  cw++;
	  refresh ();
	  sleep (3);
	  dif = 8;
	  ro = 8;
	  col = 8;
	  return;
	}
      move (y, x);
    }

  flag1 = 0;

/* before quitting the game pop up appears */
  mvprintw (LINES / 2, (COLS - 28) / 2, "Do You Want To Save The Game");
  mvprintw (LINES / 2 + 1, COLS / 2 - 3, "(y/n)?");

  while (1){

/* if y is pressed */
      if ((c = getch ()) == 'y')
	{
	  save (m);
	  first ();
	  break;
	}

/* if n is pressed */
      else if (c == 'n')
	{
	  refresh();
	  first();
	  break;
	}
    }

/* free all the elements */
  for (i = 0; i < ro; i++)
    free (m.v[i]);
  free (m.v);
  for (i = 0; i < ro; i++)
    free (m.a[i]);
  free (m.a);
  for (i = 0; i < ro; i++)
    free (m.d[i]);
  free (m.d);
  for (i = 0; i < ro; i++)
    free (m.e[i]);
  free (m.e);
  refresh ();
  clear ();
  refresh ();

/* resetting everything to default */
  dif = 8;
  ro = 8;
  col = 8;
}

void save (mine m)
{
/* writing the necessary data to files */
  FILE *fp, *gp;
  int i, j;
  char c = ' ';

  fp = fopen ("resume.txt", "w");
  gp = fopen ("resume1.txt", "w");

  if (fp == NULL){
      printf ("Operational error\n");
      perror ("a");
    }

  if (gp == NULL){
      printf ("Operational error\n");
      perror ("a");
    }

  for (i = 0; i < ro; i++){
      for (j = 0; j < col; j++)
	fprintf (fp, "%c", m.a[i][j]);
    }

  for (i = 0; i < ro; i++){
      for (j = 0; j < col; j++)
	fprintf (fp, "%c", m.d[i][j]);
    }

  for (i = 0; i < ro; i++){
      for (j = 0; j < col; j++)
	fprintf (fp, "%c", m.e[i][j]);
    }

  fprintf (fp, "%c", c);

  for (i = 0; i < ro; i++)
    {
      for (j = 0; j < col; j++)
	{
	  fprintf (fp, "%d", m.v[i][j]);
	}
    }

  fprintf (gp, "%d", m.k);
  fprintf (gp, "%c", c);
  fprintf (gp, "%d", ro);
  fprintf (gp, "%c", c);
  fprintf (gp, "%d", col);
  fprintf (gp, "%c", c);
  fprintf (gp, "%d", dif);
  fclose (fp);
  fclose (gp);

}

void printscr (int x, int y, int p, int q, mine m)
{
  int i, j;
  move (y, x);

/* for printing the red box using spaces */
  for (i = y - 1; i < y + (ro - 1) * 2 + 2; i++) {
      for (j = x - 3; j < x + (col - 1) * 4 + 4; j++)
	mvprintw (i, j, " ");
    }
  x = p;
  y = q;
  move (y, x);

/* for printing the dots */
  for (i = 0; i < ro; i++) {
      for (j = 0; j < col; j++){
	  printw ("%c", m.e[i][j]);
	  x += 4;
	  move (y, x);
	}
      x = p;
      y += 2;
      move (y, x);
    }
}

void revealmines (mine m, int p, int q)
{
  int i, j;
  for (i = 0; i < ro; i++){
      for (j = 0; j < col; j++){
	  if (m.a[i][j] == '*')
	    mvprintw ((2 * i) + q, (4 * j) + p, "*");
	}
    }
}

int opn (int i, int j, int i1, int j1, int p, int q, mine m)
{
/* if the neighbour does not exist then return */
  if ((i + i1) < 0 || ((i + i1) > (col - 1)) || ((j + j1) < 0)
      || ((j + j1) > (ro - 1)))
    return 0;

/* if neighbour exists and is equal to # then print # */
  else if (m.d[j + j1][i + i1] == '#')
    mvprintw (((j + j1) * 2) + q, ((i1 + i) * 4) + p, "%c",
	      m.d[j + j1][i1 + i]);

/* if the tile exists and is not a flagged one then unveil the tile */
  else
    {
      m.e[j + j1][i1 + i] = m.a[j + j1][i1 + i];
      mvprintw (((j + j1) * 2) + q, ((i1 + i) * 4) + p, "%c",
		m.e[j + j1][i1 + i]);
      return 0;
    }
}

/* the function openmine uses recursion */
int openmine (int y, int x, int p, int q, mine m)
{
  int i = 0, j = 0;
/* calculating the position in the array using the positoin of the cusror on the screen */
  j = (y - q) / 2;
  i = (x - p) / 4;
  refresh ();

/* if the tile contains nothing */
  if (m.a[j][i] == ' ')
    {
      m.v[j][i] = 1;

/* unveil all the neighbouring tiles */
      opn (i, j, 1, -1, p, q, m);
      opn (i, j, 1, 0, p, q, m);
      opn (i, j, 1, 1, p, q, m);
      opn (i, j, 0, 1, p, q, m);
      opn (i, j, -1, 1, p, q, m);
      opn (i, j, -1, 0, p, q, m);
      opn (i, j, -1, -1, p, q, m);
      opn (i, j, 0, -1, p, q, m);

/* in every if condition below i am checking whether the neighbouring tile exists and if it is visited or not */
      if (!((i + 1) < 0) && !((j + -1) < 0) && !((col - 1) < (i + 1))
	  && !((ro - 1) < (j + -1)) && !m.v[j + -1][i + 1]){
	  openmine (2 * (j + -1) + q, 4 * (i + 1) + p, p, q, m);
	}
      refresh ();

      if (!((i + 1) < 0) && !((j + 0) < 0) && !((col - 1) < (i + 1))
	  && !((ro - 1) < (j + 0)) && !m.v[j + 0][i + 1]){
	  openmine (2 * (j + 0) + q, 4 * (i + 1) + p, p, q, m);
	}
      refresh ();

      if (((i + 1) >= 0) && ((j + 1) >= 0) && ((col - 1) >= (i + 1))
	  && ((ro - 1) >= (j + 1)) && !m.v[j + 1][i + 1]){
	  openmine (2 * (j + 1) + q, 4 * (i + 1) + p, p, q, m);
	}
      refresh ();

      if (!((i + 0) < 0) && !((j + 1) < 0) && !((col - 1) < (i + 0))
	  && !((ro - 1) < (j + 1)) && !m.v[j + 1][i + 0]){
	  openmine (2 * (j + 1) + q, 4 * (i + 0) + p, p, q, m);
	}
      refresh ();

      if (!((i + -1) < 0) && !((j + 1) < 0) && !((col - 1) < (i + -1))
	  && !((ro - 1) < (j + 1)) && !m.v[j + 1][i + -1]){
	  openmine (2 * (j + 1) + q, 4 * (i + -1) + p, p, q, m);
	}
      refresh ();

      if (!((i + -1) < 0) && !((j + 0) < 0) && !((col - 1) < (i + -1))
	  && !((ro - 1) < (j + 0)) && !m.v[j + 0][i + -1]){
	  openmine (2 * (j + 0) + q, 4 * (i + -1) + p, p, q, m);
	}
      refresh ();

      if (!((i + -1) < 0) && !((j + -1) < 0) && !((col - 1) < (i + -1))
	  && !((ro - 1) < (j + -1)) && !m.v[j + -1][i + -1]){
	  openmine (2 * (j + -1) + q, 4 * (i + -1) + p, p, q, m);
	}
      refresh ();

      if (!((i + 0) < 0) && !((j + -1) < 0) && !((col - 1) < (i + 0))
	  && !((ro - 1) < (j + -1)) && !m.v[j + -1][i + 0]){
	  openmine (2 * (j + -1) + q, 4 * (i + 0) + p, p, q, m);
	}
      refresh ();

    }
  return 0;
}


void easy ()
{

  system ("clear");


  ro = 8;
  col = 8;
  game ();


  return;

}

void inter ()
{

  system ("clear");

/* Setting no. of rows and columns */
  ro = 12;
  col = 12;
  game ();


  return;

}

void diff ()
{

  system ("clear");

  ro = 16;
  col = 16;
  game ();

  return;
}

void custom ()
{

  system ("clear");

/* Taking no. of rows and columns from user */
  mvprintw ((LINES - 4) / 2, (COLS - 26) / 2, "Enter the number of rows: ");
  refresh ();

/* taking input from the user for the no. of rows */
  scanf ("%d", &ro);
  printw ("%d", ro);
  refresh ();
  mvprintw (LINES / 2, (COLS - 28) / 2, "Enter the number of columns: ");
  refresh ();

/* taking input from the user for the no. of columns */
  scanf ("%d", &col);
  printw ("%d", col);
  refresh ();
  sleep (3);

  game ();
 return;


}

void chanmine ()
{

  system ("clear");
  mvprintw ((LINES - 4) / 2, (COLS - 26) / 2, "Enter the no. of mines: ");
  refresh ();

/* taking input from the user for the no. of rows */
  scanf ("%d", &dif);
  printw ("%d", dif);
  refresh ();
  sleep (2);
  newer (1);
  
  return;

}

void first ()
{

  int highlight = 1;
  int choice = 0;
  int c;
  int y, x;

  initscr ();
  getmaxyx (stdscr, y, x);

  clear ();
  noecho ();
  cbreak ();

 /* New window opened */
  menu = newwin (y - 10, x - 10, 5, 5);

  start_color ();
  init_pair (1, COLOR_BLACK, COLOR_YELLOW);
  wbkgd (menu, COLOR_PAIR (1));

  keypad (menu, TRUE);

/* Erasing everything on the window */ 
 erase();
/* Printing text on the window */
  mvprintw (2, 2,
	    "Use arrow keys to go up and down. Press 'Enter' to select a choice");
  refresh ();

  print_menu (menu, highlight);

/* For highlighting the option */
  while (1)
    {

      c = wgetch (menu);

      switch (c)
	{
	case KEY_UP:
	  if (highlight == 1)
	    highlight = n_choices;
	  else
	    --highlight;
	  break;
	case KEY_DOWN:
	  if (highlight == n_choices)
	    highlight = 1;
	  else
	    ++highlight;
	  break;
	case 10:
	  choice = highlight;
	  break;
	default:

	  refresh ();
	  break;
	}
      print_menu (menu, highlight);
      if (choice != 0)
	{

	  newer (choice);
	  break;

	}
   }

  clrtoeol ();
  refresh ();
/* Closing the opened window */
  endwin ();

}



void grid (int ch)
{

  int y, x;
  switch (ch)
    {

    case 1:
      easy ();
      break;

    case 2:
      inter ();
      break;

    case 3:
      diff ();
      break;

    case 4:
      custom ();
      break;

    case 5:
      break;
    }

 first();
 return;

}

void print_menu (WINDOW * menu, int highlight)
{
  int x, y, i, z, d;

  initscr ();
/* Gets the x and y coordinates of the screen */
  getmaxyx (menu, y, x);
  z = y / 2;
  d = x / 2.3;
  mvwprintw (menu, y / 8, x / 2.5, "%s", "Minesweeper");

  box (menu, 0, 0);

  for (i = 0; i < n_choices; ++i)
    {
      if (highlight == i + 1)	/* Highlights the present choice */
	{

	  wattron (menu, A_REVERSE);
	  mvwprintw (menu, z, d, "%s", choices[i]);
	  wattroff (menu, A_REVERSE);
	}
      else
	mvwprintw (menu, z, d, "%s", choices[i]);


      ++z;
    }

/*  Refreshes the window */ 
   wrefresh (menu);

}

void print_menu6 (WINDOW * win7, int highlight)
{
  int x, y, i, z, d;


  initscr ();

  start_color ();
  init_pair (1, COLOR_BLACK, COLOR_YELLOW);
  wbkgd (win7, COLOR_PAIR (1));

  getmaxyx (win7, y, x);
  z = y / 2;
  d = x / 2.3;

  box (win7, 0, 0);

  for (i = 0; i < n_choices6; ++i)
    {
      if (highlight == i + 1)	/* Highlights the present choice */
	{

	  wattron (win7, A_REVERSE);
	  mvwprintw (win7, z, d, "%s", choices6[i]);
	  wattroff (win7, A_REVERSE);
	}
      else
	mvwprintw (win7, z, d, "%s", choices6[i]);

      ++z;
    }

  wrefresh (win7);

}

void print_menu1 (WINDOW * win, int highlight)
{
  int x, y, i, z, d;


  initscr ();
  getmaxyx (win, y, x);
  z = y / 2;
  d = x / 2.3;

  erase();
  mvwprintw (win, y / 6, x / 2.5, "%s", "Levels: ");

  box (win, 0, 0);

  for (i = 0; i < n_choices1; ++i)
    {
      if (highlight == i + 1)	/* Highlight the present choice */
	{
	  wattron (win, A_REVERSE);
	  mvwprintw (win, z, d, "%s", choices1[i]);
	  wattroff (win, A_REVERSE);
	}
      else
	mvwprintw (win, z, d, "%s", choices1[i]);


      ++z;
    }

  wrefresh (win);
}

void print_menu2 (WINDOW * win1, int highlight)
{
  int x, y, i, z, d;

  initscr ();
  getmaxyx (win1, y, x);
  z = y / 2;
  d = x / 2.3;


  box (win1, 0, 0);

  for (i = 0; i < n_choices2; ++i)
    {
      if (highlight == i + 1)	/* Highlight the present choice */
	{
	  wattron (win1, A_REVERSE);
	  mvwprintw (win1, z, d, "%s", choices2[i]);
	  wattroff (win1, A_REVERSE);
	}
      else
	mvwprintw (win1, z, d, "%s", choices2[i]);


      ++z;
    }

  wrefresh (win1);
}

void newer (int choice)
{
  int x, y, c = 0, highlight = 1, choice1 = 0, choice6 = 0;
  int i, z, d;

  switch (choice)
    {
    case 1:
      initscr ();
      getmaxyx (stdscr, y, x);

      clear ();
      noecho ();
      cbreak ();

      win = newwin (y - 10, x - 10, 5, 5);

      start_color ();
      init_pair (1, COLOR_BLACK, COLOR_YELLOW);
      wbkgd (win, COLOR_PAIR (1));

      keypad (win, TRUE);

      erase();
      mvprintw (2, 2,
		"Use arrow keys to go up and down. Press 'Enter' to select a choice");
      refresh ();

      print_menu1 (win, highlight);

      while (1)
	{

	  c = wgetch (win);

	  switch (c)
	    {
	    case KEY_UP:
	      if (highlight == 1)
		highlight = n_choices1;
	      else
		--highlight;
	      break;
	    case KEY_DOWN:
	      if (highlight == n_choices1)
		highlight = 1;
	      else
		++highlight;
	      break;
	    case 10:
	      choice1 = highlight;
	      break;
	    default:

	      refresh ();
	      break;
	    }
	  print_menu1 (win, highlight);
	  if (choice1 != 0)
	    {
	      grid (choice1);
	      break;
	    }


	}


      clrtoeol ();
      refresh ();
      endwin ();
      break;

    case 2:
      initscr ();
      getmaxyx (stdscr, y, x);

      clear ();
      noecho ();
      cbreak ();

      win7 = newwin (y - 10, x - 10, 5, 5);

      start_color ();
      init_pair (1, COLOR_BLACK, COLOR_YELLOW);
      wbkgd (win1, COLOR_PAIR (1));

      keypad (win7, TRUE);

      erase();
      mvprintw (2, 2,
		"Use arrow keys to go up and down. Press 'Enter' to select a choice");
      refresh ();

      print_menu6 (win7, highlight);

      while (1)
	{

	  c = wgetch (win7);

	  switch (c)
	    {
	    case KEY_UP:
	      if (highlight == 1)
		highlight = n_choices6;
	      else
		--highlight;
	      break;
	    case KEY_DOWN:
	      if (highlight == n_choices6)
		highlight = 1;
	      else
		++highlight;
	      break;
	    case 10:
	      choice6 = highlight;
	      break;
	    default:
	      refresh ();
	      break;
	    }
	  print_menu6 (win7, highlight);

	  if (choice6 != 0)
	    {
	      print6 (choice6);
	      break;

	    }
	}
      clrtoeol ();
      refresh ();
      endwin ();
      break;

    case 3:
      initscr ();
      getmaxyx (stdscr, y, x);

      clear ();
      noecho ();
      cbreak ();

      win1 = newwin (y - 10, x - 10, 5, 5);

      start_color ();
      init_pair (1, COLOR_BLACK, COLOR_YELLOW);
      wbkgd (win1, COLOR_PAIR (1));

      keypad (win1, TRUE);

      erase();
      mvprintw (2, 2,
		"Use arrow keys to go up and down. Press 'Enter' to select a choice");
      refresh ();

      print_menu2 (win1, highlight);

      while (1)
	{

	  c = wgetch (win1);

	  switch (c)
	    {
	    case KEY_UP:
	      if (highlight == 1)
		highlight = n_choices2;
	      else
		--highlight;
	      break;
	    case KEY_DOWN:
	      if (highlight == n_choices2)
		highlight = 1;
	      else
		++highlight;
	      break;
	    case 10:
	      choice1 = highlight;
	      break;
	    default:

	      refresh ();
	      break;
	    }
	  print_menu2 (win1, highlight);

	  if (choice1 != 0)
	    {
	      print3 (choice1);
	      break;

	    }
	}

      clrtoeol ();
      refresh ();
      endwin ();
      break;


    case 4:
      system ("clear");
      exit (0);


    }
 return;

}

void print3 (int choice1)
{

  int x, y, c = 0;
  int i, z, d, t;

  switch (choice1)
    {
    case 1:
      initscr ();
      getmaxyx (stdscr, y, x);

      clear ();
      noecho ();
      cbreak ();

      win3 = newwin (y - 10, x - 10, 5, 5);

      start_color ();
      init_pair (1, COLOR_BLACK, COLOR_YELLOW);
      wbkgd (win3, COLOR_PAIR (1));

      erase();
      mvprintw (2, 2,
	       "Press any key to exit");
      refresh ();

      keypad (win3, TRUE);


      z = 3;
      d = 6;


      box (win3, 0, 0);

      for (i = 0; i < n_choices3; ++i)
	{


	  mvwprintw (win3, z, d, "%s", choices3[i]);


	  ++z;
	}

      wrefresh (win3);


      while (1)
	{

	  c = wgetch (win3);

	  if (c != 0)
	    break;

	}





      clrtoeol ();
      refresh ();
      endwin ();
      newer (3);
      break;

    case 2:
      initscr ();
      getmaxyx (stdscr, y, x);

      clear ();
      noecho ();
      cbreak ();

      win5 = newwin (y - 10, x - 10, 5, 5);

      start_color ();
      init_pair (1, COLOR_BLACK, COLOR_YELLOW);
      wbkgd (win5, COLOR_PAIR (1));

      erase();
      mvprintw (2, 2,
	       "Press any key to exit");
      refresh ();

      keypad (win5, TRUE);


      z = y / 5;
      d = x / 3;


      box (win5, 0, 0);

      for (i = 0; i < n_choices5; ++i)
	{


	  mvwprintw (win5, z, d, "%s", choices5[i]);


	  ++z;
	}

      wrefresh (win5);


      while (1)
	{

	  c = wgetch (win5);

	  if (c != 0)
	    break;

	}





      clrtoeol ();
      refresh ();
      endwin ();

      newer (3);
      break;

    case 3:
      first ();
      break;

    }
}


void print6 (int choice6)
{

  switch (choice6)
    {
    case 1:
      resume ();
      break;

    case 2:
      chanmine ();
      break;
	
    case 3:
      stats();
      break;
 
    case 4:
      break;

    }
 
   first();
   return;

}

void stats(){

      int z, d, c = 0;
      
 initscr ();
      getmaxyx (stdscr, y, x);

      clear ();
      noecho ();
      cbreak ();

      wins = newwin (y - 10, x - 10, 5, 5);

      start_color ();
      init_pair (1, COLOR_BLACK, COLOR_YELLOW);
      wbkgd (wins, COLOR_PAIR (1));

      erase();
      mvprintw (2, 2,
	       "Press any key to exit");
      refresh ();

      z = y / 5;
      d = x / 3;

      box (wins, 0, 0);
	
      keypad (wins, TRUE);

       	  mvwprintw (wins, z, d, "%s ", "Total games: ");
	  mvwprintw (wins, z, (d + sizeof("Total games: ")), "%d ", (cw+cl));
          ++z;
           mvwprintw (wins, z, d, "%s ", "Games won: ");
	  mvwprintw (wins, z, (d + sizeof("Games won: ")), "%d ", cw);
          ++z;
          mvwprintw (wins, z, d, "%s ", "Games lost: ");
	  mvwprintw (wins, z, (d + sizeof("Games lost: ")), "%d ", cl);
          
      wrefresh (wins);
	
      while (1)
	{

	  c = wgetch(wins);

	  if (c != 0)
	    break;

	}
      
      clrtoeol ();
      refresh ();
      endwin ();

      return;

}
