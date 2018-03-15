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
	} player;
	struct {
		vec2i pos;
		rect bounds;
		char disp_char;
	}myball;
	struct {
		int total;
		vec2i pos[200];//up to 200 bricks possitions in array
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
						brick--;
						score = score + 10;
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
						brick--;
						score = score + 10;
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
						brick--;
						score = score + 10;
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
						brick--;
						score = score + 10;
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
		if (myball.pos.y + 2 <= screen_area.top() + 2 && myball.pos.x - 1 <= 0) { //Fixed bug for right top corner.
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
				else { score -= 7; }

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
	void run(int &finalscore) {
		int go = 0;
		initscr();
		cbreak();
		noecho();
		clear();
		refresh();
		int SpeedX, SpeedY;
		SpeedX = 1;
		SpeedY = -1;
		myball.pos = { 25,20 };
		player.pos = { 25, 22 };
		//Color codes for my game.
		start_color();
		init_pair(1, COLOR_CYAN, COLOR_BLACK);
		init_pair(2, COLOR_WHITE, COLOR_BLACK);
		init_pair(3, COLOR_BLUE, COLOR_BLACK);
		init_pair(4, COLOR_RED, COLOR_BLACK);
		init_pair(5, COLOR_GREEN, COLOR_BLACK);
		init_pair(6, COLOR_YELLOW, COLOR_BLACK);
		init_pair(7, COLOR_MAGENTA, COLOR_BLACK);
		//Loop to make score and tick values to be set only once.
		int once = 0;
		int score;
		int tick;
		if (once == 0) {
			score = 300;
			tick = 0;
			once++;
		}
		int count;//Number of bricks in game
		int hb = 1; // brick stack height stacks at hb
		int mult = 0; // width of bricks displayed in the middle of brick initialisation cycle.
		int v = 0; // number of bricks displayed in the middle of brick initialisation cycle.
		srand(time(NULL));
		count = rand() % 70 + 13;
		int calc = 0;
		int brick = 0;
		//Counts bricks at the beggining of the game// 
		if (calc == 0) {
			brick = count;
			calc++;
		}
		//initialises bricks in map.
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

		// draw box around screen
		attron(A_BOLD);
		wattron(main_wnd, COLOR_PAIR(3));
		box(main_wnd, 0, 0);
		wattroff(main_wnd, COLOR_PAIR(3));
		attroff(A_BOLD);
		wrefresh(main_wnd);
		wrefresh(game_wnd);
		//Game cycle.
		while (1) {

			wclear(game_wnd);
			wattron(game_wnd, COLOR_PAIR(3));
			attron(A_BOLD);//draws a box for game window.
			box(game_wnd, 0, 0);
			attroff(A_BOLD);
			wattroff(game_wnd, COLOR_PAIR(3));

			in_char = wgetch(main_wnd);//takes the input
			in_char = tolower(in_char);//makes the input lower case


			mvaddch(player.pos.y, player.pos.x, '_');
			mvaddch(myball.pos.y, myball.pos.x, 'O');
			bool move = true; //Starts ball movement.
			if (move == true) {
				ballmove(SpeedX, SpeedY, player.pos.x, player.pos.y, count, go, score, brick);
				Sleep(90);
			}
			//While player is in-game, his score decereases. (Time multiplier).
			if (go == 0) {
				if (tick == 100) {
					tick = 0;
					score -= 1;
				}
				if (tick < 100) {
					tick++;
				}
			}
			//If there are no bricks, game is over, player Won.
			if (brick == 0) {
				go = 1;
			}
			wattron(main_wnd, COLOR_PAIR(6));
			mvwprintw(main_wnd, 2, 59, "CONTROLS:");
			mvwprintw(main_wnd, 3, 59, "A or <- move left");
			mvwprintw(main_wnd, 4, 59, "D or -> move right");
			wattron(main_wnd, COLOR_PAIR(6));
			wattron(main_wnd, COLOR_PAIR(5));
			mvwprintw(main_wnd, 10, 59, "score: %d", score);
			wattroff(main_wnd, COLOR_PAIR(5));
			wattron(main_wnd, COLOR_PAIR(4));
			mvwprintw(main_wnd, 11, 59, "bricks: %d", brick);
			wattroff(main_wnd, COLOR_PAIR(4));
			//If the game is over, clear window, print out score.
			if (go == 1) {
				werase(main_wnd);
				// If there are some bricks on the map, player loses score according to bricks left.
				if (brick != 0) {
					int penalty = brick * 3;
					mvwprintw(main_wnd, 7, 20, "You have received death penalty, points lost: %d ", penalty);
					finalscore = score - brick * 3;
				}
				//If person destroys all the bricks, he gets 300 points.
				else {
					finalscore = score + 300;
					mvwprintw(main_wnd, 7, 20, "CONGRATULATIONS! You smashed through the firewall! , you receive 300 points.");
					mvwprintw(main_wnd, 8, 30, "You receive 300 points.");

				}
				go = 2;
				if (go == 2) {
					myball.pos.x = -1;
					myball.pos.y = -1;
					//Print the score.
					mvwprintw(main_wnd, 10, 35, "Score: %d", finalscore);
					mvwprintw(main_wnd, 11, 25, " Press any key to continue...");
					wrefresh(game_wnd);
					wrefresh(main_wnd);
					getch();
					return;
				}
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
				//Draws pad.
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
			init();//initialise screen
			int finalscore;
			run(finalscore);//runs the game, returns score.
			clear();// clears screen
			int rc;
			sqlite3 *db;
			rc = sqlite3_open("stux_base.db", &db);
			sqlite3_stmt * stmt;
			int highscore;
			string sqlSelect = "SELECT brickBreaker FROM minigameScores where userName = 'Nick'";//Takes highscore from database and compares with curent score.
			sqlite3_prepare(db, sqlSelect.c_str(), sqlSelect.size(), &stmt, nullptr);
			sqlite3_step(stmt);
			highscore = sqlite3_column_int(stmt,0);
			sqlite3_finalize(stmt);
			if (highscore > finalscore) {//If the score is lower, makes highscore the curent score.
				finalscore = highscore;
			}
			cout << finalscore << endl;
			std::string s = std::to_string(finalscore);//Pushes curent score to database.
			sqlSelect = "UPDATE minigameScores SET brickBreaker = ";
			sqlSelect.append(s);
			string end = " WHERE userName = 'Nick'";
			sqlSelect.append(end);
			sqlite3_prepare(db, sqlSelect.c_str(), sqlSelect.size(), &stmt, nullptr);
			sqlite3_step(stmt);
			sqlite3_finalize(stmt);
			sqlite3_close(db);
		}
