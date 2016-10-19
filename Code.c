#include "init.h"


int main()
{	
	
	first();
	return 0;
}

void init_mines(void * ptr)
{
	mine_t (*m)[width] = ptr;
	for ( i = 0; i < height; i++)
 for (j = 0; j < width; j++)
		if (rand() % mine_ratio)
			m[i][j].flag = M_NONE;
		else {
			m[i][j].flag = M_MINED;
			n_mines ++;
		}

	for ( i = 0; i < height; i++)
 for (j = 0; j < width; j++){
		m[i][j].cnt = 0;
		for (x = j - 1; x <= j + 1; x++) {
			if (x < 0 || x > width) continue;
			for (y = i - 1; y <= i + 1; y++) {
				if (y < 0 || y >= width) continue;
				m[i][j].cnt += 1 && (m[y][x].flag & M_MINED);
			}
		}
	}
}

int mine_clear(void *ptr, int x, int y, int mass_clear)
{
	mine_t (*m)[width] = ptr;
	unsigned short flag;
	if (x < 0 || x >= width || y < 0 || y >= height)
		return 1;
	flag = m[y][x].flag;

	if (((flag & M_CLEARED) && 1) != mass_clear) return 1;

	if ((flag & M_MINED) && !(flag & M_MARKED)) {
		m[y][x].flag |= M_BOMBED;
		reveal = 1;
		return 0;
	}

	if (!(flag & M_MARKED))
		flag = (m[y][x].flag |= M_CLEARED);

	if (m[y][x].cnt && !mass_clear) return 1;
	if (flag & M_MARKED) return 1;

	for ( i = y - 1; i <= y + 1; i++)
		for ( j = x - 1; j <= x + 1; j++)
			if (!mine_clear(ptr, j, i, 0)) return 0;
	return 1;
}

void mine_mark(void *ptr, int x, int y)
{
	mine_t (*m)[width] = ptr;
	if (m[y][x].flag & M_CLEARED) return;
	if (m[y][x].flag & M_MARKED)
		n_mines ++;
	else
		n_mines --;
	m[y][x].flag ^= M_MARKED;
}

int check_wining(void *ptr)
{
	mine_t (*m)[width] = ptr;
	int good = 1;
	for (i = 0; i < height; i++)
 for (j = 0; j < width; j++) {
		int f = m[i][j].flag;
		if ((f & M_MINED) && !(f & M_MARKED)) {
			m[i][j].flag = M_BOMBED;
			good = 0;
		}
	}
	mvwprintw(wrap, height + 1, 0, good ? "All clear!    " : "BOOM!           ");

	reveal = 1;
	return good;
}

void repaint(void *ptr)
{
	mine_t (*m)[width] = ptr, *p;
	box(winn, 0, 0);
	for ( i = 0; i < height; i++)
 for ( j = 0; j < width; j++) {
		char c;
		p = &m[i][j];
		int f = p->flag;
		if (reveal)
			c = (f & M_BOMBED) ? 'X' : (f & M_MINED) ? 'o' : ' ';
		else if (p->flag & M_BOMBED)
			c = 'X';
		else if (p->flag & M_MARKED)
			c = '?';
		else if (p->flag & M_CLEARED)
			c = p->cnt ? p->cnt + '0' : ' ';
		else
			c = '.';
		mvwprintw(winn, i + 1, 2 * j + 1, " %c", c);
	}
	if (reveal);
	else if (n_mines)
		mvwprintw(wrap, height + 1, 0, "Mines:%6d   ", n_mines);

	else
		 mvwprintw(wrap, height + 1, 0, "Claim victory?    ");

	wrefresh(wrap);
	wrefresh(winn);
}

void easy(){
	
	system("clear");

MEVENT evt;

		height = 8;
		width = 8;
	
	
	initscr();
	int mines[height][width];
	init_mines(mines);

	winn = newwin(height + 2, 2 * width + 2, 0, 0);
	wrap = newwin(height + 3, 2 * width + 2, 1, 0);

start_color();
	init_pair(1,COLOR_BLACK, COLOR_YELLOW);
	wbkgd(winn, COLOR_PAIR(1));

	keypad(wrap, 1);
	mousemask(BUTTON1_CLICKED | BUTTON2_CLICKED | BUTTON3_CLICKED, 0);
	while (1) {
		int ch;
		repaint(mines);
		if ((ch = wgetch(wrap)) != KEY_MOUSE) {
			if (ch != 'r') break;
			reveal = !reveal;
			continue;
		}

		if (getmouse(&evt) != OK) continue;

		if ((evt.bstate & BUTTON1_CLICKED)) {
			if (evt.y == height + 2 && !n_mines) {
				check_wining(mines);
				break;
			}
			if (!mine_clear(mines, (evt.x - 1) / 2, evt.y - 1, 0))
				break;
		}
		else if ((evt.bstate & BUTTON2_CLICKED)) {
			if (!mine_clear(mines, (evt.x - 1) / 2, evt.y - 1, 1))
				break;
		}
		else if ((evt.bstate & BUTTON3_CLICKED))
			mine_mark(mines, (evt.x - 1)/2, evt.y - 1);
	}
	repaint(mines);

	mousemask(0, 0);
	keypad(wrap, 0);
	endwin();
first();
	
}

void inter(){
	
	system("clear");

MEVENT evt;
	
	
	
		height = 16;
		width = 16;
	
	
	initscr();
	int mines[height][width];
	init_mines(mines);

	winn = newwin(height + 2, 2 * width + 2, 0, 0);
	wrap = newwin(height + 3, 2 * width + 2, 1, 0);

start_color();
	init_pair(1,COLOR_BLACK, COLOR_YELLOW);
	wbkgd(winn, COLOR_PAIR(1));

	keypad(wrap, 1);
	mousemask(BUTTON1_CLICKED | BUTTON2_CLICKED | BUTTON3_CLICKED, 0);
	while (1) {
		int ch;
		repaint(mines);
		if ((ch = wgetch(wrap)) != KEY_MOUSE) {
			if (ch != 'r') break;
			reveal = !reveal;
			continue;
		}

		if (getmouse(&evt) != OK) continue;

		if ((evt.bstate & BUTTON1_CLICKED)) {
			if (evt.y == height + 2 && !n_mines) {
				check_wining(mines);
				break;
			}
			if (!mine_clear(mines, (evt.x - 1) / 2, evt.y - 1, 0))
				break;
		}
		else if ((evt.bstate & BUTTON2_CLICKED)) {
			if (!mine_clear(mines, (evt.x - 1) / 2, evt.y - 1, 1))
				break;
		}
		else if ((evt.bstate & BUTTON3_CLICKED))
			mine_mark(mines, (evt.x - 1)/2, evt.y - 1);
	}
	repaint(mines);

	mousemask(0, 0);
	keypad(wrap, 0);
	endwin();
first();
	
}

void diff(){
	
	system("clear");

MEVENT evt;
	
	
	
		height = 22;
		width = 22;
	
	
	initscr();
	int mines[height][width];
	init_mines(mines);

	winn = newwin(height + 2, 2 * width + 2, 0, 0);
	wrap = newwin(height + 3, 2 * width + 2, 1, 0);

start_color();
	init_pair(1,COLOR_BLACK, COLOR_YELLOW);
	wbkgd(winn, COLOR_PAIR(1));

	keypad(wrap, 1);
	mousemask(BUTTON1_CLICKED | BUTTON2_CLICKED | BUTTON3_CLICKED, 0);
	while (1) {
		int ch;
		repaint(mines);
		if ((ch = wgetch(wrap)) != KEY_MOUSE) {
			if (ch != 'r') break;
			reveal = !reveal;
			continue;
		}

		if (getmouse(&evt) != OK) continue;

		if ((evt.bstate & BUTTON1_CLICKED)) {
			if (evt.y == height + 2 && !n_mines) {
				check_wining(mines);
				break;
			}
			if (!mine_clear(mines, (evt.x - 1) / 2, evt.y - 1, 0))
				break;
		}
		else if ((evt.bstate & BUTTON2_CLICKED)) {
			if (!mine_clear(mines, (evt.x - 1) / 2, evt.y - 1, 1))
				break;
		}
		else if ((evt.bstate & BUTTON3_CLICKED))
			mine_mark(mines, (evt.x - 1)/2, evt.y - 1);
	}
	repaint(mines);

	mousemask(0, 0);
	keypad(wrap, 0);
	endwin();
first();
	
}

void custom(){
	
	system("clear");

int a,b;

MEVENT evt;
	
	scanf("%d%d", &a, &b);
	
		height = a;
		width = b;
	
	
	initscr();
	int mines[height][width];
	init_mines(mines);

	winn = newwin(height + 2, 2 * width + 2, 0, 0);
	wrap = newwin(height + 3, 2 * width + 2, 1, 0);

start_color();
	init_pair(1,COLOR_BLACK, COLOR_YELLOW);
	wbkgd(winn, COLOR_PAIR(1));

	keypad(wrap, 1);
	mousemask(BUTTON1_CLICKED | BUTTON2_CLICKED | BUTTON3_CLICKED, 0);
	while (1) {
		int ch;
		repaint(mines);
		if ((ch = wgetch(wrap)) != KEY_MOUSE) {
			if (ch != 'r') break;
			reveal = !reveal;
			continue;
		}

		if (getmouse(&evt) != OK) continue;

		if ((evt.bstate & BUTTON1_CLICKED)) {
			if (evt.y == height + 2 && !n_mines) {
				check_wining(mines);
				break;
			}
			if (!mine_clear(mines, (evt.x - 1) / 2, evt.y - 1, 0))
				break;
		}
		else if ((evt.bstate & BUTTON2_CLICKED)) {
			if (!mine_clear(mines, (evt.x - 1) / 2, evt.y - 1, 1))
				break;
		}
		else if ((evt.bstate & BUTTON3_CLICKED))
			mine_mark(mines, (evt.x - 1)/2, evt.y - 1);
	}
	repaint(mines);

	mousemask(0, 0);
	keypad(wrap, 0);
	endwin();
	
}

void first()
{

int highlight = 1;
	int choice = 0;
	int c;
	int y,x;
	
	initscr();
	getmaxyx(stdscr, y, x);

	clear();
	noecho();
	cbreak();	

	menu_win = newwin(y-10, x-10, 5, 5);

	start_color();
	init_pair(1,COLOR_BLACK, COLOR_YELLOW);
	wbkgd(menu_win, COLOR_PAIR(1));
	
	keypad(menu_win, TRUE);

	mvprintw(2, 2, "Use arrow keys to go up and down. Press 'Enter' to select a choice");
	refresh();

	print_menu(menu_win, highlight);

	while(1)
	{	

		c = wgetch(menu_win);

		switch(c)
		{	
			case KEY_UP:
				if(highlight == 1)
					highlight = n_choices;
				else
					--highlight;
				break;
			case KEY_DOWN:
				if(highlight == n_choices)
					highlight = 1;
				else 
					++highlight;
				break;
			case 10:
				choice = highlight;
				break;
			default:
				
				refresh();
				break;
		}
		print_menu(menu_win, highlight);
		if(choice != 0)	
		{	
			
			newer(choice); 			
			break;
		}

	}	
	
	

	clrtoeol();
	refresh();
	endwin();

}



void grid(int ch)
{

int y,x;
switch(ch)
{

case 1:	
	
	/*initscr();
	getmaxyx(stdscr, y, x);

	clear();
	noecho();
	cbreak();	

	win4 = newwin(y-10, x-10, 5, 5);

	start_color();
	init_pair(1,COLOR_BLACK, COLOR_YELLOW);
	wbkgd(win4, COLOR_PAIR(1));
	
	
	clrtoeol();
	refresh();
	endwin();
	break;*/

easy();
break;

case 2: inter();
break;

case 3: diff();
break;

case 4: custom();
break;

case 5: first();
	break;
}


}

void print_menu(WINDOW *menu_win, int highlight)
{
	int x, y, i, z, d;	

	
initscr();
	getmaxyx(menu_win, y, x);
z=y/2;
d=x/2.3;			
			mvwprintw(menu_win, y/8, x/2.5, "%s", "Minesweeper");
			
	box(menu_win, 0, 0);

	for(i = 0; i < n_choices; ++i)
	{	
		if(highlight == i + 1) /* Highlight the present choice */
		{	

			wattron(menu_win, A_REVERSE); 
			mvwprintw(menu_win, z, d, "%s", choices[i]);
			wattroff(menu_win, A_REVERSE);
		}
		else
			mvwprintw(menu_win, z, d, "%s", choices[i]);


		++z;
	}

	wrefresh(menu_win);

}

void print_menu1(WINDOW *win, int highlight)
{
	int x, y, i,z,d;	

	
initscr();
	getmaxyx(win, y, x);
z=y/2;
d=x/2.3;

mvwprintw(win, y/6, x/2.5, "%s", "Levels: ");			
			
	box(win, 0, 0);

	for(i = 0; i < n_choices1; ++i)
	{	
		if(highlight == i + 1) /* Highlight the present choice */
		{	
			wattron(win, A_REVERSE); 
			mvwprintw(win, z, d, "%s", choices1[i]);
			wattroff(win, A_REVERSE);
		}
		else
			mvwprintw(win, z, d, "%s", choices1[i]);


		++z;
	}

	wrefresh(win);
}

void print_menu2(WINDOW *win1, int highlight)
{
	int x, y, i,z,d;	

	
initscr();
	getmaxyx(win1, y, x);
z=y/2;
d=x/2.3;

			
	box(win1, 0, 0);

	for(i = 0; i < n_choices2; ++i)
	{	
		if(highlight == i + 1) /* Highlight the present choice */
		{	
			wattron(win1, A_REVERSE); 
			mvwprintw(win1, z, d, "%s", choices2[i]);
			wattroff(win1, A_REVERSE);
		}
		else
			mvwprintw(win1, z, d, "%s", choices2[i]);


		++z;
	}

	wrefresh(win1);
}

void newer(int choice)
{
int x, y, c=0, highlight=1, choice1=0;
int i, z,d;

switch(choice)
{
case 1: initscr();
	getmaxyx(stdscr, y, x);

	clear();
	noecho();
	cbreak();	

	win = newwin(y-10, x-10, 5, 5);

	start_color();
	init_pair(1,COLOR_BLACK, COLOR_YELLOW);
	wbkgd(win, COLOR_PAIR(1));

	keypad(win, TRUE);

	mvprintw(2, 2, "Use arrow keys to go up and down. Press 'Enter' to select a choice");
	refresh();

	print_menu1(win, highlight);

	while(1)
	{	

		c = wgetch(win);

		switch(c)
		{	
			case KEY_UP:
				if(highlight == 1)
					highlight = n_choices1;
				else
					--highlight;
				break;
			case KEY_DOWN:
				if(highlight == n_choices1)
					highlight = 1;
				else 
					++highlight;
				break;
			case 10:
				choice1 = highlight;
				break;
			default:
				
				refresh();
				break;
		}
		print_menu1(win, highlight);
		if(choice1 != 0){
			grid(choice1);	
			break;
		}

	}	
	
	

	clrtoeol();
	refresh();
	endwin();
	break;

case 3: initscr();
	getmaxyx(stdscr, y, x);

	clear();
	noecho();
	cbreak();	

	win1 = newwin(y-10, x-10, 5, 5);

	start_color();
	init_pair(1,COLOR_BLACK, COLOR_YELLOW);
	wbkgd(win1, COLOR_PAIR(1));

	keypad(win1, TRUE);

	mvprintw(2, 2, "Use arrow keys to go up and down. Press 'Enter' to select a choice");
	refresh();

	print_menu2(win1, highlight);

	while(1)
	{	

		c = wgetch(win1);

		switch(c)
		{	
			case KEY_UP:
				if(highlight == 1)
					highlight = n_choices2;
				else
					--highlight;
				break;
			case KEY_DOWN:
				if(highlight == n_choices2)
					highlight = 1;
				else 
					++highlight;
				break;
			case 10:
				choice1 = highlight;
				break;
			default:
				
				refresh();
				break;
		}
		print_menu2(win1, highlight);

		if(choice1 != 0){
			print3(choice1);
			break;

		}
	}

	clrtoeol();
	refresh();
	endwin();
	break;



}
}

void print3(int choice1)
{

int x, y, c=0;
int i, z,d,t;

switch(choice1)
{
case 1: initscr();
	getmaxyx(stdscr, y, x);

	clear();
	noecho();
	cbreak();	

	win3 = newwin(y-10, x-10, 5, 5);

	start_color();
	init_pair(1,COLOR_BLACK, COLOR_YELLOW);
	wbkgd(win3, COLOR_PAIR(1));


	keypad(win3, TRUE);


z=3;
d=5;			
		
			
	box(win3, 0, 0);

	for(i = 0; i < n_choices3; ++i)
	{	

			
			mvwprintw(win3, z, d, "%s", choices3[i]);
		

		++z;
	}

	wrefresh(win3);

	
	while(1)
	{	

		c = wgetch(win3);

		if(c != 0)	
			break;

	}	
	
				
	


	clrtoeol();
	refresh();
	endwin();
newer(3);
	break;

case 2: initscr();
	getmaxyx(stdscr, y, x);

	clear();
	noecho();
	cbreak();	

	win5 = newwin(y-10, x-10, 5, 5);

	start_color();
	init_pair(1,COLOR_BLACK, COLOR_YELLOW);
	wbkgd(win5, COLOR_PAIR(1));


	keypad(win5, TRUE);


z=y/5;
d=x/3;			
		
			
	box(win5, 0, 0);

	for(i = 0; i < n_choices5; ++i)
	{	

			
			mvwprintw(win5, z, d, "%s", choices5[i]);
		

		++z;
	}

	wrefresh(win5);

	
	while(1)
	{	

		c = wgetch(win5);

		if(c != 0)	
			break;

	}	
	
				
	


	clrtoeol();
	refresh();
	endwin();
newer(3);
	break;

case 3: first();
break;


}	



}
