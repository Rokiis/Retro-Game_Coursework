#pragma once
#include "curses.h"
#include "BrickBreaker.cpp"
#include <cstdint>
#include <string>

struct {
    vec2i pos;
    char disp_char;
} player;


int init() {
    wnd = initscr();
    cbreak();
    noecho();
    clear();
	refresh();

	keypad(wnd, true); //Adding input for WASD buttons
	nodelay(wnd, true); //Disabling blocking for WASD buttons to lower down a latency of a click

	curs_set(0) //Hides cursor

	if(!has_colors()) {
        endwin();
        printf("ERROR: Terminal does not support color.\n");
        exit(1);
    }

     start_color();

     attron(A_BOLD);
    box(wnd, 0, 0);
	attroff(A_BOLD);

	return 0;
}

void pad(){
	int length;
	player.disp_char = '_________'
	player.pos = {10,0}

	int in_char;

	bool exit_requested = false;
}

while(1){
	in_char = wgetch(wnd);

	mvaddch(player.pos.y, player.pos.x, ' ');
	this->length = 16;
	switch(in_char) { //Enabling movement of pad
		case KEY_LEFT:
		case 'a':
			player.pos.y += 1;
			break;
		case KEY_RIGHT:
		case 'd':
			player.pos.y -= 1;
			break;
		default:
			break;
	}

	mvaddch(player.pos.y, player.pos.x, player.disp_char);

	if(exit_requested) break;

	refresh()
}mypad;

void close(){
	endwin();
}
