#include <iostream>
#include <vector>
#include <string>
#include <ncurses.h>
#include <cstdlib>
#include <unistd.h>
#ifndef PLAYER_H
#define PLAYER_H

//contans x and y coordinate of the player
struct playerpart{
    int x,y;
    playerpart(int col,int row);
    playerpart();
};

//declaring variables
class playerclass{
    int points, del, maxwidth, maxheight, lives;
    char direction, enemy, partchar, botchar, sidechar, topchar, dollar;
    bool get, shot;
    playerpart dollars;
    playerpart enemies;
    std::vector<playerpart> player;
    
    void putdollars();
    bool collision();
    void moveplayer();
    void putenemies();

public:
    playerclass();
    ~playerclass();
    void start();
};

#endif

