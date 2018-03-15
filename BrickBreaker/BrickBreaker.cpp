//BrickBreaker game, made by Rokas Navickas(navickar), member of group D2
#include <windows.h>
#include <cstdint>
#include <iostream>
#include <conio.h>
#include <thread>
#include <cmath>
#include <time.h>
#include "curses.h"
#include "Game.h"
#include <string>
#include <vector>
#include "sqlite3.h"
using namespace std;

//Initialisation of windows, game window and score window(main window).
WINDOW* main_wnd;
WINDOW* game_wnd;
rect game_area;
rect screen_area;
vec2ui cur_size;
//Structures for pad, bricks and ball.
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
	//Function to move a ball around a map, bounce from walls, corners and pad, collide with bricks, to make them disappear. Increase score when player hits brick, decrease score with every bounce from pad.
	void ballmove(int &speedX, int &speedY, int x, int y, int count, int &go, int &score, int &brick) {// Ball movement function
		if (myball.pos.x == -1 && myball.pos.y == -1) {
			speedX = 0;
			speedY = 0;
		}
		if (speedX > 0) {//If the ball is moving from left to right:
			for (int i = 0; i < count; i++) {//Brick Collision
				if (myball.pos.y == bricks.pos[i].y + 1) { //If the ball is comming from top.
					if ((myball.pos.x + 1 == bricks.pos[i].x - 2) || (myball.pos.x + 1 == bricks.pos[i].x - 1) || (myball.pos.x + 1 == bricks.pos[i].x) || (myball.pos.x + 1 == bricks.pos[i].x + 1) || (myball.pos.x + 1 == bricks.pos[i].x + 2)) {
						brick= brick -1;
						score = score + 100;
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
					if ((myball.pos.x + 1 == bricks.pos[i].x - 2) || (myball.pos.x + 1 == bricks.pos[i].x - 1) || (myball.pos.x + 1 == bricks.pos[i].x) || (myball.pos.x + 1 == bricks.pos[i].x + 1) || (myball.pos.x + 1 == bricks.pos[i].x + 2)) {
						brick= brick - 1 ;
						score = score + 100;
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
						brick = brick - 1;
						score = score + 100;
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
						brick= brick-1;
						score = score + 100;
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

		if (myball.pos.y + 2 <= screen_area.top() + 2 && myball.pos.x + 2 == screen_area.width() - 21) { //Fixed bug for left top corner.
			speedY = speedY * -1;
			speedX = speedX * -1;
			myball.pos.x += 1 * speedX;
			myball.pos.y += 1 * speedY;
		}
		if (myball.pos.y + 2 <= screen_area.top() + 2 && myball.pos.x - 2 <= 0) {
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
		if (myball.pos.x - 1 == 0) { //If the ball bounces from the left side, horizontal speed inverts.
			speedX = speedX * -1;
			myball.pos.x += 1 * speedX;
			myball.pos.y += 1 * speedY;
		}
		if (myball.pos.y + 1 == y) { // x and y are coords of a pad... If a ball is in the same height as pad, and in the same coords as pad, vertical speed inverts.
			if ((myball.pos.x + 2 == x) || (myball.pos.x + 1 == x) || (myball.pos.x == x) || (myball.pos.x - 1 == x) || (myball.pos.x - 2 == x)) {
				if (score <= 0) {
					score = 0;
				}
				else { 
					//score -= 150;
				}

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
	//Create a screen for game and main windows. 
	int init() {
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
		game_area = { { 0, 0 },{ screen_area.width() - 1, screen_area.height() } };

		// enable function keys
		keypad(main_wnd, true);
		keypad(game_wnd, true);

		// disable input blocking
		nodelay(main_wnd, true);
		nodelay(game_wnd, true);




		return 0;
	}
	//Game loop.
	void run() {
		int go = 0;
		initscr();
		cbreak();
		noecho();
		clear();
		refresh();
		int SpeedX, SpeedY;
		SpeedX = 1;
		SpeedY = -1;
		myball.disp_char = 'o';
		myball.pos = { 25,20 };
		player.disp_char = '|';
		player.pos = { 25, 22 };
		bricks.disp_char = '*';
		start_color();
		init_pair(1, COLOR_CYAN, COLOR_BLACK);
		init_pair(2, COLOR_WHITE, COLOR_BLACK);
		init_pair(3, COLOR_BLUE, COLOR_BLACK);
		init_pair(4, COLOR_RED, COLOR_BLACK);
		init_pair(5, COLOR_GREEN, COLOR_BLACK);
		init_pair(6, COLOR_YELLOW, COLOR_BLACK);
		init_pair(7, COLOR_MAGENTA, COLOR_BLACK);
		//mvwprintw(main_wnd, 10, 60, "SCORE:");
		int once = 0;
		int score;
		if (once == 0) {
			score = 1000;
			once++;
		}
		int count;//Number of bricks in game
		int hb = 1;
		int mult = 0;
		int v = 0;
		srand(time(NULL));
		count = rand() % 70 + 13;
		for (int i = 0; i < count; i++) {
			if ((5 + v + mult) > (screen_area.width() - 30)) {
				hb++;
				v = 0;
			}
			mult = 5 * v;
			bricks.pos[i].y = hb; //makes gaps between rows.
			bricks.pos[i].x = 5 + v + mult;
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
		//Game cycle.
		while (1) {

			wclear(game_wnd);

			attron(A_BOLD);//draws a box for game window.
			box(game_wnd, 0, 0);
			attroff(A_BOLD);


			in_char = wgetch(main_wnd);//takes the input
			in_char = tolower(in_char);//makes the input lower case


			mvaddch(player.pos.y, player.pos.x, '_');
			mvaddch(myball.pos.y, myball.pos.x, 'O');
			//While player is in-game, his score decereases. (Time multiplier).
			if (go == 0) {
				score = score - 1;
			}
			int calc = 0;
			int brick = 0;//Counts bricks at the beggining of the game// 
			if (calc == 0) {
				brick = count;
				calc= 2;
				mvwprintw(main_wnd, 12, 59, "bricksxxx: %d", brick);
			}
			mvwprintw(main_wnd, 10, 59, "score: %d", score);
			mvwprintw(main_wnd, 11, 59, "bricks: %d", brick);
			bool move = true; //Starts ball movement.
			if (move == true) {
				ballmove(SpeedX, SpeedY, player.pos.x, player.pos.y, count, go, score, brick);
				Sleep(90);
			}
			//If there are no bricks, game is over, player Won.
			if (brick <= 1) {
				go = 1;
			}
			//If the game is over, clear window, print out score.
			if (go == 1) {
				werase(main_wnd);
				int finalscore;
				int one = 0;
				if (one == 0) {
					if (brick != 0) {
						finalscore = score - 1000;
					}
					else { finalscore = score; }
					one++;
				}
				if (brick != 0) { mvwprintw(main_wnd, 7, 20, "You have received death penalty, you lost 1000 points"); }
				else {
					mvwprintw(main_wnd, 7, 20, "CONGRATULATIONS! You smashed through the firewall! ");
				}
				mvwprintw(main_wnd, 10, 35, "score: %d", finalscore);
			}


			else {

				switch (in_char) {//Input function.
				case KEY_LEFT:
				case 'a':
					if (player.pos.x - 3 <= screen_area.left() + 2) {//Move to the left. If its near the left side, does not allow move more.
						break;
					}
					else {
						player.pos.x -= 3;
					}
					break;
				case KEY_RIGHT:
				case 'd':
					if (player.pos.x + 3 >= screen_area.right() - 24) { // move to the right. If its near the right side of game window, does not allow to move more.
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
				if (never == 0) { //Create bricks, ONCE
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
				refresh();
			}
		}
	}
	int main() {
		sqlite3 *db;
		char *zErrMsg = 0;
		int rc;

		rc = sqlite3_open("stux_base.db", &db);

		if (rc) {
			fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
			return(0);
		}
		else {
			fprintf(stderr, "Opened database successfully\n");
		}
		sqlite3_close(db);
		init();
		run();
}