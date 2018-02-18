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
//int onPlay = 1;
//const int W = 50;           //game field size
//const int H = 20;
//int score;
//int board[100][100];
//enum eDirection { STOP = 0, LEFT, RIGHT}; //movement
//eDirection dir;
WINDOW* main_wnd;
WINDOW* game_wnd;

int left, right, top, bottom, tlc, trc, blc, brc;
/*char lr = '|';
char corners = '+';			//used for setting specific characters for border
char tb = '-';*/
left = right = 0;
top = bottom = 0;
tlc = trc = blc = brc = 0;
wborder(game_wnd, left, right, top, bottom, tlc, trc, blc, brc);

rect game_area;
rect screen_area;

vec2ui cur_size;

ObjectField bricks;

struct {
	vec2i pos;
	rect bounds;
	char disp_char;
	int lives;
} player;

struct{
	vec2i pos;
	rect bounds;
	char disp_char;
}myball;

int init() {

	srand(time(0));
	main_wnd = initscr();
	cbreak();
	noecho();
	clear();
	refresh();
	curs_set(0);
	start_color();


	screen_area = { { 0, 0 },{ 80, 24 } };
	int infopanel_height = 4;
	game_wnd = newwin(screen_area.height() - infopanel_height - 2,
		screen_area.width() - 2,
		screen_area.top() + 1,
		screen_area.left() + 1);

	main_wnd = newwin(screen_area.height(), screen_area.width(), 0, 0);

	game_area = { { 0, 0 },{ screen_area.width() - 2, screen_area.height() - infopanel_height - 4 } };


	// enable function keys
	keypad(main_wnd, true);
	keypad(game_wnd, true);

	// disable input blocking
	nodelay(main_wnd, true);
	nodelay(game_wnd, true);

	if (!has_colors()) {
		endwin();
		printf("ERROR: Terminal does not support color.\n");
		exit(1);
	}



	return 0;
}

int speedX, speedY;
void ballmove() { //NEEDS SOME MAJOR FIXES ON BALL MOVEMENT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	for (size_t i = 0; i < bricks.getData().size(); i++) {
		myball.pos.y -= 1;
		myball.pos.x += 1;
		if (myball.bounds.contains(bricks.getData().at(i).getPos())) {
			bricks.erase(i);
			speedX = -1 * speedX;

		}
	}
	
}

void run() {
	initscr();
	cbreak();
	noecho();
	clear();
	refresh();
	int tick;
	myball.disp_char = 'o';
	myball.pos = { 20,14 };
	player.disp_char = '|';
	player.pos = { 20, 17 };

	bricks.setBounds(game_area);

	int in_char = 0;
	bool exit_requested = false;
	bool game_over = false;

	// draw box around screen
	attron(A_BOLD);
	box(main_wnd, 0, 0);
	attroff(A_BOLD);

	wmove(main_wnd, game_area.bot() + 3, 1);
	whline(main_wnd, '-', screen_area.width() - 2);

	wrefresh(main_wnd);
	wrefresh(game_wnd);

	tick = 0;

	while (1) {
		werase(game_wnd);

		in_char = wgetch(main_wnd);
		in_char = tolower(in_char);

		mvaddch(player.pos.y, player.pos.x, ' ');
		mvaddch(myball.pos.y, myball.pos.x, ACS_DARROW);

		switch (in_char) {
			case ' ':
				ballmove();
				break;
			case KEY_LEFT:
			case 'a':
				player.pos.x -= 1;
				break;
			case KEY_RIGHT:
			case 'd':
				player.pos.x += 1;
				break;
			default:
				break;
		}

		if (tick % 10 == 0)
			bricks.update();

		player.bounds = { { player.pos.x , player.pos.y}, 1, 1 };
		myball.bounds = { { myball.pos.x , myball.pos.y }, 1, 1 };
		for (size_t i = 0; i < bricks.getData().size(); i++) {
			if (myball.bounds.contains(bricks.getData().at(i).getPos())) {
				bricks.erase(i);
			}
		}

		for (auto a : bricks.getData()) {
			wattron(game_wnd, A_BOLD);
			mvwaddch(game_wnd, a.getPos().y, a.getPos().x, '*');
			wattroff(game_wnd, A_BOLD);
		}

		wattron(game_wnd, A_ALTCHARSET);
		mvwaddch(game_wnd, player.pos.y, player.pos.x - 2, ACS_LARROW);
		mvwaddch(game_wnd, player.pos.y, player.pos.x - 1, ACS_LARROW);
		mvwaddch(game_wnd, player.pos.y, player.pos.x , '_');
		mvwaddch(game_wnd, player.pos.y, player.pos.x + 1, ACS_RARROW);
		mvwaddch(game_wnd, player.pos.y, player.pos.x + 2, ACS_RARROW);
		mvwaddch(game_wnd, myball.pos.y, myball.pos.x, 'O');

		wattroff(game_wnd, A_ALTCHARSET);

		wrefresh(main_wnd);
		wrefresh(game_wnd);
		if (exit_requested || game_over) break;

		tick++;

		refresh();
	}
}


void close() {
	delwin(main_wnd);
	delwin(game_wnd);
	endwin();
}



/*
void gotoXY(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void resetboard() {
	for (int j = 0; j<H; j++) {
		for (int i = 0; i<W; i++) {
			board[i][j] = 0;
		}
	}
}
void drawPoint(int x, int y, int value) {
	board[x][y] = value;
}
void erasePoint(int x, int y) {
	board[x][y] = 0;
}
void drawBorder() {
	for (int i = 0; i<W; i++) { drawPoint(i, 0, 1); }
	for (int i = 0; i<W; i++) { drawPoint(i, H - 1, 1); }
	for (int j = 0; j<H; j++) { drawPoint(0, j, 1); }
	for (int j = 0; j<H; j++) { drawPoint(W - 1, j, 1); }
}





*


//BRICKS
class bricks {
public:
	void init(int startX, int startY) {
		for (int j = 0; j < H; j++) {
			for (int i = 0; i < W; i++) {
				if (i >= startX & i < W - startX & j >= startY & j < startY + 4) { board[i][j] = 2; }
			}
		}
	}
	void vanish(int x, int y) {
		board[x][y] = 0;
	}
	int x, y, stat;
	void draw() {
		drawPoint(x, y, 2);
	}
};*/


/*

bricks myBrks;
ball myBall;
void startGame() {
	int lose = 0;
	system("cls");
	score = 0;
	onPlay = 1;
	resetboard();
	drawBorder();

	myPad.init();
	myBall = ball();
	myBall.draw();
	myBrks.init(7, 4);

	while (onPlay) {
		myBall.move();
		myBall.checkbounce();
		myBall.checkcollision();
		myBall.checkbound(onPlay, lose);


		for (int j = 0; j < H; j++) {
			for (int i = 0; i < W; i++) {
				gotoXY(i, j);
				if (board[i][j] == 1) { cout << "8"; }
				else if (board[i][j] == 2) { cout << "0"; }
				else if (board[i][j] == 3) { cout << "0"; }
				else if (board[i][j] == 4) { cout << "0"; }
				else { cout << " "; }
			}
		}

		gotoXY(65, 4);
		cout << "SCORE:" << score;
	}
}
	//


int main() {
	initscr();
	cbreak();
	noecho();
	clear();
	refresh();

	while (1);
	thread second(listenInput);
	Input();
	startGame();
	second.detach();
	return 0;
}*/
