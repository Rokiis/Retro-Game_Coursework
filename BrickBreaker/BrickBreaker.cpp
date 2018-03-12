//brick destroyer game
//Rnavick
#pragma comment(lib, "User32.lib")
#include <windows.h>
#include <cstdint>
#include <iostream>
#include <conio.h>
#include <thread>
#include <cmath>
#include <time.h>
#include "curses.h"
#include "Game.h"
#include "ObjectField.h"
#include <string>
#include <vector>
using std::vector;

WINDOW* main_wnd;
WINDOW* game_wnd;



rect game_area;
rect screen_area;

vec2ui cur_size;

//ObjectField bricks;
int timer = 0;
struct {
	vec2i pos;
	rect bounds;
	char disp_char;
	int lives;
} player;

struct {
	vec2i pos;
	rect bounds;
	char disp_char;
}myball;

struct {
	int total;
	vec2i pos[200];
	rect bounds;
	char disp_char;
} bricks;




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////BALL MOVEMENT/////////////////////
void ballmove(int &speedX, int &speedY, int x, int y, int count,int &go) {// Ball movement function
	if (myball.pos.x == -1 && myball.pos.y == -1) {
		speedX = 0;
		speedY = 0;
	}
	if (speedX > 0) {//If the ball is moving from left to right:
		for (int i = 0; i < count; i++) {//Brick Collision
			if (myball.pos.y == bricks.pos[i].y + 1) { //If the ball is comming from top.
				if ((myball.pos.x + 1 == bricks.pos[i].x - 2) || (myball.pos.x + 1 == bricks.pos[i].x - 1) || (myball.pos.x + 1 == bricks.pos[i].x) || (myball.pos.x + 1 == bricks.pos[i].x + 1) || (myball.pos.x + 1 == bricks.pos[i].x + 2)) {
					speedY = speedY * -1;
					myball.pos.x += 1 * speedX;
					myball.pos.y += 1 * speedY;
					bricks.pos[i].x = -5;
					bricks.pos[i].y = -5;
					attron(A_BOLD);
					mvwaddch(game_wnd, bricks.pos[i].y, bricks.pos[i].x - 2, ' ');
					mvwaddch(game_wnd, bricks.pos[i].y, bricks.pos[i].x - 1, ' ');
					mvwaddch(game_wnd, bricks.pos[i].y, bricks.pos[i].x, ' ');
					mvwaddch(game_wnd, bricks.pos[i].y, bricks.pos[i].x + 1, ' ');
					mvwaddch(game_wnd, bricks.pos[i].y, bricks.pos[i].x + 2, ' ');
					attroff(A_BOLD);

				}
			}
			if (myball.pos.y == bricks.pos[i].y - 1) { //If the ball is comming from bottom.
				if ((myball.pos.x + 1 == bricks.pos[i].x - 2) || (myball.pos.x + 1 == bricks.pos[i].x - 1) || (myball.pos.x +1 == bricks.pos[i].x) || (myball.pos.x + 1 == bricks.pos[i].x + 1) || (myball.pos.x +1 == bricks.pos[i].x + 2)) {
					speedY = speedY * -1;
					myball.pos.x += 1 * speedX;
					myball.pos.y += 1 * speedY;
					bricks.pos[i].x = -5;
					bricks.pos[i].y = -5;
					attron(A_BOLD);
					mvwaddch(game_wnd, bricks.pos[i].y, bricks.pos[i].x - 2, ' ');
					mvwaddch(game_wnd, bricks.pos[i].y, bricks.pos[i].x - 1, ' ');
					mvwaddch(game_wnd, bricks.pos[i].y, bricks.pos[i].x, ' ');
					mvwaddch(game_wnd, bricks.pos[i].y, bricks.pos[i].x + 1, ' ');
					mvwaddch(game_wnd, bricks.pos[i].y, bricks.pos[i].x + 2, ' ');
					attroff(A_BOLD);
				}
			}
		}
	}

	if (speedX < 0) {//If the ball is moving from right to left:
		for (int i = 0; i < count; i++) {//Brick Collision
			if (myball.pos.y == bricks.pos[i].y + 1) { //If the ball is comming from top.
				if ((myball.pos.x - 1 == bricks.pos[i].x - 2) || (myball.pos.x - 1 == bricks.pos[i].x - 1) || (myball.pos.x - 1 == bricks.pos[i].x) || (myball.pos.x - 1 == bricks.pos[i].x + 1) || (myball.pos.x - 1 == bricks.pos[i].x + 2)) {
					speedY = speedY * -1;
					myball.pos.x += 1 * speedX;
					myball.pos.y += 1 * speedY;
					bricks.pos[i].x = -5;
					bricks.pos[i].y = -5;
					attron(A_BOLD);
					mvwaddch(game_wnd, bricks.pos[i].y, bricks.pos[i].x - 2, ' ');
					mvwaddch(game_wnd, bricks.pos[i].y, bricks.pos[i].x - 1, ' ');
					mvwaddch(game_wnd, bricks.pos[i].y, bricks.pos[i].x, ' ');
					mvwaddch(game_wnd, bricks.pos[i].y, bricks.pos[i].x + 1, ' ');
					mvwaddch(game_wnd, bricks.pos[i].y, bricks.pos[i].x + 2, ' ');
					attroff(A_BOLD);
				}
			}
			if (myball.pos.y == bricks.pos[i].y - 1) { //If the ball is comming from bottom.
				if ((myball.pos.x - 1 == bricks.pos[i].x - 2) || (myball.pos.x - 1 == bricks.pos[i].x - 1) || (myball.pos.x - 1 == bricks.pos[i].x) || (myball.pos.x - 1 == bricks.pos[i].x - 1) || (myball.pos.x - 1 == bricks.pos[i].x + 2)) {
					speedY = speedY * -1;
					myball.pos.x += 1 * speedX;
					myball.pos.y += 1 * speedY;
					bricks.pos[i].x = -5;
					bricks.pos[i].y = -5;
					attron(A_BOLD);
					mvwaddch(game_wnd, bricks.pos[i].y, bricks.pos[i].x - 2, ' ');
					mvwaddch(game_wnd, bricks.pos[i].y, bricks.pos[i].x - 1, ' ');
					mvwaddch(game_wnd, bricks.pos[i].y, bricks.pos[i].x, ' ');
					mvwaddch(game_wnd, bricks.pos[i].y, bricks.pos[i].x + 1, ' ');
					mvwaddch(game_wnd, bricks.pos[i].y, bricks.pos[i].x + 2, ' ');
					attroff(A_BOLD);
				}
			}
		}
	}

	if (myball.pos.y + 2 <= screen_area.top() +2 && myball.pos.x + 2 == screen_area.width() - 21) { //Fixed bug for left top corner.
		speedY = speedY * -1;
		speedX = speedX * -1;
		myball.pos.x += 1 * speedX;
		myball.pos.y += 1 * speedY;
	}
	if (myball.pos.y + 2 == screen_area.top() + 2) { //If the ball bounces from top of the map, vertical speed inverts
		speedY = speedY * -1;
		myball.pos.x += 1 * speedX;
		myball.pos.y += 1 * speedY;
	}
	if (myball.pos.x + 2 == screen_area.width() - 21) {// If the ball bounces from the right side, horizontal speed inverts.
		speedX = speedX * -1;
		myball.pos.x += 1 * speedX;
		myball.pos.y += 1 * speedY;
	}
	if (myball.pos.x -1 == 0) { //If the ball bounces from the left side, horizontal speed inverts.
		speedX = speedX * -1;
		myball.pos.x += 1 * speedX;
		myball.pos.y += 1 * speedY;
	}
	if (myball.pos.y + 1 == y) { // x and y are coords of a pad... If a ball is in the same height as pad, and in the same coords as pad, vertical speed inverts.
		if ((myball.pos.x + 2 == x) || (myball.pos.x + 1 == x) || (myball.pos.x == x) || (myball.pos.x - 1 == x) || (myball.pos.x - 2 == x)) {
			speedY = speedY * -1;
			myball.pos.x += 1 * speedX;
			myball.pos.y += 1 * speedY;
		}
		else {
			myball.pos.x = -1;
			myball.pos.x = -1;
			go = 1;
		}
	}
	else { // else, if ball does not bounce to anything, it just moves the same direction as before.
		myball.pos.x += 1 * speedX;
		myball.pos.y += 1 * speedY;
		refresh();
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////MAIN GAME LOOP///////////////
int init() {
	srand(time(0)); //Randomisation 
	main_wnd = initscr(); //Initialise screen in main window.
	cbreak();
	noecho();
	clear();
	refresh();
	curs_set(0);
//Default curses initialisation to remove flickering.




	screen_area = { { 0, 0 },{ 80, 24 } }; //Screen area coordinates.
	int infopanel_width = 20; //Info panel initialisation, to write score, instructions etc.
	game_wnd = newwin(screen_area.height(), // Making an actual game window.
		screen_area.width() - infopanel_width - 1,
		screen_area.top(),
		screen_area.left());
	main_wnd = newwin(screen_area.height(), screen_area.width(), 0, 0);
	game_area = { { 0, 0 },{ screen_area.width() - 1, screen_area.height()} };

	// enable function keys
	keypad(main_wnd, true);
	keypad(game_wnd, true);

	// disable input blocking
	nodelay(main_wnd, true);
	nodelay(game_wnd, true);




	return 0;
}


void run() {
	int go = 0;
	initscr();
	cbreak();
	noecho();
	clear();
	refresh();
	int tick;
	int SpeedX, SpeedY;
	SpeedX = 1;
	SpeedY = -1;
	myball.disp_char = 'o';
	myball.pos = { 25,20 };
	player.disp_char = '|';
	player.pos = { 25, 22};
	bricks.disp_char = '*';
	start_color();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	init_pair(2, COLOR_WHITE, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_RED, COLOR_BLACK);
	init_pair(5, COLOR_GREEN, COLOR_BLACK);
	init_pair(6, COLOR_YELLOW, COLOR_BLACK);
	init_pair(7, COLOR_MAGENTA, COLOR_BLACK);

	int count;//Number of bricks in game
	int hb = 1;
	int len;
	int mult = 0;
	int v = 0;
	int a[200];
	srand(time(NULL));
		count = rand() % 70 + 13;
	for (int i=0; i<count; i++){
		if ((7 + v + mult) > (screen_area.width()-30)) {
			hb++;
			v = 0;
		}
		mult = 5 * v;
		bricks.pos[i].y =hb; //makes gaps between rows.
		bricks.pos[i].x =7+ v+mult;
		v++;
	}
	int in_char = 0;
	bool exit_requested = false;
	bool game_over = false;

	// draw box around screen
	attron(A_BOLD);
	box(main_wnd, 0, 0);
	box(game_wnd, 0, 0);
	attroff(A_BOLD);
	wrefresh(game_wnd);



	wrefresh(main_wnd);
	wrefresh(game_wnd);
	while (1) {
		tick = 0;

		wclear(game_wnd);

		attron(A_BOLD);//draws a box for game window.
		box(game_wnd, 0, 0);
		attroff(A_BOLD);


		in_char = wgetch(main_wnd);//takes the input
		in_char = tolower(in_char);//makes the input lower case


		mvaddch(player.pos.y, player.pos.x, '_');
		mvaddch(myball.pos.y, myball.pos.x, 'O');
		

		bool move = true; //Starts ball movement.
		if (move == true) {
			ballmove(SpeedX, SpeedY, player.pos.x, player.pos.y,count,go);
			Sleep(90);
		}
		if (go == 1) {
			close();
		}


		else {  }


		switch (in_char) {//Input function.
		case KEY_LEFT:
		case 'a':
			if (player.pos.x -3 <= screen_area.left()+2) {//Move to the left. If its near the left side, does not allow move more.
				break;
			}
			else {
				player.pos.x -= 3; }
			break;
		case KEY_RIGHT:
		case 'd':
			if (player.pos.x +3>= screen_area.right() - 24) { // move to the right. If its near the right side of game window, does not allow to move more.
				break;
			}
			else {
				player.pos.x += 3;
			}
			break;
		default:
			break;
		}


		player.bounds = { { player.pos.x , player.pos.y }, 1, 5 };
		myball.bounds = { { myball.pos.x , myball.pos.y }, 1, 1 };
		srand(time(NULL));
		int never = 0;
		wattron(game_wnd, A_BOLD);
		if (never == 0) {
			for (int i = 0; i < count; i++) {
				wattron(game_wnd, COLOR_PAIR(5));
				int z = rand() % 10;
				if (z % 2 == 0) {
					mvwaddch(game_wnd, bricks.pos[i].y, bricks.pos[i].x - 2, '1');
				}
				if (z % 2 != 0) {
					mvwaddch(game_wnd, bricks.pos[i].y, bricks.pos[i].x - 2, '0');
				}
				z = rand() % 10;
				if (z % 2 == 0) {
					mvwaddch(game_wnd, bricks.pos[i].y, bricks.pos[i].x - 1, '1');
				}
				if (z % 2 != 0) {
					mvwaddch(game_wnd, bricks.pos[i].y, bricks.pos[i].x - 1, '0');
				}
				z = rand() % 10;
				if (z % 2 == 0) {
					mvwaddch(game_wnd, bricks.pos[i].y, bricks.pos[i].x, '1');
				}
				if (z % 2 != 0) {
					mvwaddch(game_wnd, bricks.pos[i].y, bricks.pos[i].x, '0');
				}
				z = rand() % 10;
				if (z % 2 == 0) {
					mvwaddch(game_wnd, bricks.pos[i].y, bricks.pos[i].x + 1, '1');
				}
				if (z % 2 != 0) {
					mvwaddch(game_wnd, bricks.pos[i].y, bricks.pos[i].x + 1, '0');
				}
				z = rand() % 10;
				if (z % 2 == 0) {
					mvwaddch(game_wnd, bricks.pos[i].y, bricks.pos[i].x + 2, '1');
				}
				if (z % 2 != 0) {
					mvwaddch(game_wnd, bricks.pos[i].y, bricks.pos[i].x + 2, '0');
				}
				wattroff(game_wnd, COLOR_PAIR(5));
			}
			never++;
		}
		else {}
		wattroff(game_wnd, A_BOLD);

		wattron(game_wnd, A_ALTCHARSET);
		mvwaddch(game_wnd, player.pos.y, player.pos.x - 2, ACS_LARROW);
		mvwaddch(game_wnd, player.pos.y, player.pos.x - 1, ACS_LARROW);
		mvwaddch(game_wnd, player.pos.y, player.pos.x, '_');
		mvwaddch(game_wnd, player.pos.y, player.pos.x + 1, ACS_RARROW);
		mvwaddch(game_wnd, player.pos.y, player.pos.x + 2, ACS_RARROW);
		wattroff(game_wnd, A_ALTCHARSET);
		wattron(game_wnd, A_BOLD);
		mvwaddch(game_wnd, myball.pos.y, myball.pos.x, 'O');
		wattroff(game_wnd, A_BOLD);

		wrefresh(main_wnd);
		wrefresh(game_wnd);

		tick++;

		refresh();
	}
}


void close() {
	delwin(game_wnd);
	delwin(main_wnd);
	endwin();
}
