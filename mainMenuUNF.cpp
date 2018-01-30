#include "curses.h" // or #include <ncurses.h> (linux) sudo apt-get install libncurses5-dev libncursesw5-dev
#include <iostream>
#include <string>
using namespace std;

int main()
{        
	initscr();	
	noecho(); //turns off showing what key the user pressed
	start_color(); //enables colours 
	int height, width, start_y, start_x;
	height = 20;
	width = 70;
	start_y = 1;
	start_x = 1;

	WINDOW * win = newwin(height, width, start_y, start_x); //create window
	refresh(); //refresh screen to allow window

	
	//box(win, 0, 0); //create box, takes characters to form box edges e.g char c = 'g'; box(win, (int)c, 0);
	int left, right, top, bottom, tlc, trc, blc, brc;
	/*char lr = '|';
	char corners = '+';			//used for setting specific characters for border
	char tb = '-';*/
	left = right = 0;
	top = bottom = 0;
	tlc = trc = blc = brc = 0;
	wborder(win, left, right, top, bottom, tlc, trc, blc, brc);
	
	/*char* stux1 = "___ _____ _   ___  __  _  _ ___ _____";
	char* stux2 = "/ __|_   _| | | \ \/ / | \| | __|_   _|";
	char* stux3 = "\__ \ | | | |_| |>  < | .` | _|  | |";				//play around with this to get it to work
	char* stux4 = "|___/ |_|  \___//_/\_\ |_|\_|___| |_|";*/

	char* stux1 = "___ _____ _   ___  __  _  _ ___ _____";
	char* stux2 = "/ __|_   _| | | \ \/ / | \| | __|_   _|";
	char* stux3 = "\__ \ | | | |_| |>  < | .` | _|  | |";					//won't work on codio, works on win10 vis 2017 with pdcurses
	char* stux4 = "|___/ |_|  \___//_/\_\ |_|\_|___| |_|";
	
	

	init_pair(1, COLOR_GREEN, 0);
	wattron(win, COLOR_PAIR(1));
	mvwprintw(win, 1.1, 15, stux1);
	mvwprintw(win, 2, 15, stux2);
	mvwprintw(win, 3.1, 15, stux3);
	mvwprintw(win, 4, 15, stux4);
    mvwprintw(win, 5, 15, "Stuxnet V1.0 - Group D2");

	wattroff(win, COLOR_PAIR(1));

	init_pair(2, COLOR_CYAN, 0);
	wattron(win, COLOR_PAIR(2));
	/*mvwprintw(win, 7, 2, "1. Login");
	mvwprintw(win, 10, 2, "2. Register");*/
	wattroff(win, COLOR_PAIR(1));

	wrefresh(win); //refreshes specfic window
	keypad(win, true);

	string choices[2] = { "LOGIN", "REGISTER" };
	int choice;
	int highlight = 0;
	while (1)
	{
		for (int i = 0; i < 2; i++)
		{
			if (i == highlight)
				wattron(win, A_REVERSE);
			mvwprintw(win, i + 7, 2, choices[i].c_str());
			wattroff(win, A_REVERSE);
		}
		choice = wgetch(win);

		switch (choice)
		{
		case KEY_UP:
			highlight--;
			if (highlight == -1)
				highlight = 0;
			break;
		case KEY_DOWN:
			highlight++;
			if (highlight == 2)
				highlight = 1;
			break;
		default:
			break;
		}
		if (choice == 10)
			break;
	}
	mvwprintw(win, 15, 2, "You have selected to %s. Press any key to continue...", choices[highlight].c_str());
	string x = choices[highlight];
	wrefresh(win);
	if (x == "LOGIN")
	{
		mvwprintw(win, 15, 2, "You have selected to login. Press any key to continue...");
		wrefresh(win);
		getch();
		WINDOW * login = newwin(20, 70, 1, 1);		//creates new window
		refresh();
		wborder(login, 0, 0, 0, 0, 0, 0, 0, 0);		//sets window border
		wattron(login, COLOR_PAIR(1));
		mvwprintw(login, 1, 30, "LOGIN");
		wattroff(login, COLOR_PAIR(1));
		wattron(login, COLOR_PAIR(2));
		mvwprintw(login, 7, 2, "USERNAME: ");
		mvwprintw(login, 10, 2, "PASSWORD: ");
		wrefresh(login);
	}
	if (x == "REGISTER")
	{
		mvwprintw(win, 15, 2, "You have selected to register. Press any key to continue...");
		wrefresh(win);
		getch();
		WINDOW * register1 = newwin(20, 70, 1, 1);
		refresh();
		wborder(register1, 0, 0, 0, 0, 0, 0, 0, 0);
		wattron(register1, COLOR_PAIR(1));
		mvwprintw(register1, 1, 30, "REGISTER");
		wattroff(register1, COLOR_PAIR(1));
		wattron(register1, COLOR_PAIR(2));
		mvwprintw(register1, 7, 2, "USERNAME: ");
		mvwprintw(register1, 10, 2, "PASSWORD: ");
		wrefresh(register1);
	}
	

	/*int c = wgetch(win);
	if (c == '1')
	{
		mvwprintw(win, 15, 2, "You have selected to login. Press any key to continue...");
		wrefresh(win);
		getch();
		WINDOW * login = newwin(20, 70, 1, 1);		//creates new window
		refresh();
		wborder(login, 0, 0, 0, 0, 0, 0, 0, 0);		//sets window border

		init_pair(3, COLOR_GREEN, 0);
		init_pair(4, COLOR_CYAN, 0);
		wattron(login, COLOR_PAIR(3));
		mvwprintw(login, 1, 30, "LOGIN");
		wattroff(login, COLOR_PAIR(3));
		wattron(login, COLOR_PAIR(4));
		mvwprintw(login, 7, 2, "USERNAME: ");
		mvwprintw(login, 10, 2, "PASSWORD: ");
		wrefresh(login);

	}
	if (c == '2')
	{
		mvwprintw(win, 15, 2, "You have selected to register. Press any key to continue...");
		wrefresh(win);
	}
	*/

	getch(); //wait for user input, returns int value of key

	endwin();

	return 0;
}
