#include <iostream>
#include <ncurses.h>
#include <string>
#include <algorithm>
#include "sqlite3.h"
#include <ctime>
using namespace std;
bool miningLoop = false;
int passiveIncome(int time1, int time2, int mult)
{
    int diff = time2 - time1;
    if(diff>=10)
    {
       int gain = (diff/10)*mult;
       return gain;
    }
    else
        return 0;
}
class MainGamePlayer
{
public:
	string name;
	int strikes;			//used for main menu stats only
	int cash;
    int perClick;
    int passive;
    time_t lastOnline;
};
void printMiddle(WINDOW * win, int y, int x, int upDown, string asd) 
{
	int getLength = asd.length();									 
	int newY = (y / 2) - upDown;
	int newX = (x - getLength) / 2;
	mvwprintw(win, newY, newX, asd.c_str());
}
int main()
{    
    MainGamePlayer mainPlayer;
    int rc;
    sqlite3 *db;
    rc = sqlite3_open("stux_base.db", &db);
    sqlite3_stmt * stmt;
    string sqlSelect = "SELECT cash, strikes,lastOnline FROM mainGamePlayer where name = 'Nick';";
    sqlite3_prepare(db, sqlSelect.c_str(), sqlSelect.size(), &stmt, nullptr);
    sqlite3_step(stmt);
    mainPlayer.cash =  sqlite3_column_int(stmt, 0);
    mainPlayer.strikes =  sqlite3_column_int(stmt, 1); 
    mainPlayer.lastOnline =  sqlite3_column_int(stmt, 2);
    sqlite3_finalize(stmt);
    sqlSelect = "SELECT perClick, passive FROM dataMining where name = 'Nick';";
    sqlite3_prepare(db, sqlSelect.c_str(), sqlSelect.size(), &stmt, nullptr);
    sqlite3_step(stmt);
    mainPlayer.perClick = sqlite3_column_int(stmt, 0);
    mainPlayer.passive = sqlite3_column_int(stmt, 1);
    
    int gain = passiveIncome(mainPlayer.lastOnline, time(nullptr), mainPlayer.passive);
    mainPlayer.cash += gain;
    sqlite3_finalize(stmt); 
    sqlite3_close(db);
    //cout<<mainPlayer.lastOnline<<endl;
    //cout<< time(nullptr)<<endl;
    while(!miningLoop)
    {
        
        initscr();
        noecho();
        curs_set(0);
        start_color();
        WINDOW * miningMenu = newwin(20, 70 , 1 , 1);
        refresh();
        wborder(miningMenu, 0 , 0 , 0 , 0 , 0 , 0 , 0, 0);
        string miningTitle = "Data mining rig";
        int miningMaxY, miningMaxX;
        getmaxyx(miningMenu, miningMaxY, miningMaxX);
        
        init_pair(1, COLOR_GREEN, 0);
		init_pair(69, COLOR_RED, 0);	//colour initialisations
		init_pair(2, COLOR_CYAN, 0);
		init_pair(3, COLOR_MAGENTA, 0);
		init_pair(4, COLOR_WHITE, 0);
		init_pair(5, COLOR_YELLOW, 0);
        
        wattron(miningMenu, COLOR_PAIR(1));
        printMiddle(miningMenu, miningMaxY,miningMaxX, 9 ,miningTitle);
        wattroff(miningMenu, COLOR_PAIR(1));
        
        wattron(miningMenu, COLOR_PAIR(5));
			mvwprintw(miningMenu, 1, 55, "CASH: %d", mainPlayer.cash);
		wattroff(miningMenu, COLOR_PAIR(5));
        
        
        
        keypad(miningMenu, true);
        string miningMenuOptions[4] = {"Mine","Upgrade manual mining", "Upgrade passive mining rig", "Go back"};
        int miningMenuChoice;
        int miningMenuHighlight = 0;
        while(1)
        {
            wattron(miningMenu, COLOR_PAIR(2));
            for(int i=0; i<4;i++)
            {
                if(i == miningMenuHighlight)
                    wattron(miningMenu, A_REVERSE);
                mvwprintw(miningMenu, 5*i + 3, 3, miningMenuOptions[i].c_str());
                wattroff(miningMenu, A_REVERSE); 
            }
            wattroff(miningMenu, COLOR_PAIR(2));
            for(int i =0; i<4;i++)
            {
            if(miningMenuOptions[i] == "Mine")
                {
                    wattron(miningMenu, COLOR_PAIR(69));
                        mvwprintw(miningMenu, 5*i+3 , 8,"+%d", mainPlayer.perClick);
                    wattroff(miningMenu,COLOR_PAIR(69));
                }
                if(miningMenuOptions[i] == "Upgrade manual mining")
                {
                    wattron(miningMenu, COLOR_PAIR(69));
                        mvwprintw(miningMenu, 5*i+3 , 25,"costs: %d",100*mainPlayer.perClick);
                    wattroff(miningMenu,COLOR_PAIR(69));
                }
                if(miningMenuOptions[i] == "Upgrade passive mining rig")
                {
                   wattron(miningMenu, COLOR_PAIR(69));
                        mvwprintw(miningMenu, 5*i+3 , 26,"earning: %d/10sec",mainPlayer.passive);
                        mvwprintw(miningMenu, 5*i+3 , 43,"costs: %d",50*mainPlayer.passive);
                   wattroff(miningMenu,COLOR_PAIR(69)); 
                }
            }
        miningMenuChoice = wgetch(miningMenu);
        switch(miningMenuChoice)
        {
                case KEY_UP:
                    miningMenuHighlight--;
                    if(miningMenuHighlight == -1)
                        miningMenuHighlight = 3;
                    break;
                case KEY_DOWN:
                    miningMenuHighlight++;
                    if(miningMenuHighlight == 4)
                        miningMenuHighlight = 0;
                    break;
                default:
                    break;
        }
            
        if(miningMenuChoice == 10)
            break;
        }
        
        string miningMenuInput = miningMenuOptions[miningMenuHighlight];
        wrefresh(miningMenu);
        if(miningMenuInput == "Go back")
        {
            miningLoop = true;
            refresh();
            
        }
        if(miningMenuInput == "Mine")
        {
            mainPlayer.cash+=mainPlayer.perClick;
            wattron(miningMenu, COLOR_PAIR(5));
                mvwprintw(miningMenu, 1, 55, "CASH: %d", mainPlayer.cash);
            wattroff(miningMenu, COLOR_PAIR(5));
            refresh();
        }
        if(miningMenuInput == "Upgrade manual mining")
        {
            if(mainPlayer.cash>=100*mainPlayer.perClick)
            {
                mainPlayer.cash-=100*mainPlayer.perClick;
                mainPlayer.perClick+=1;
            }
            
        }
        if(miningMenuInput == "Upgrade passive mining rig")
        {
            if(mainPlayer.cash>=50*mainPlayer.passive)
            {
                mainPlayer.cash-=50*mainPlayer.passive;
                mainPlayer.passive+=1;
            }
        }
        wrefresh(miningMenu);
        }
    endwin();
    mainPlayer.lastOnline = time(nullptr);
    rc = sqlite3_open("stux_base.db", &db);
    sqlSelect = "UPDATE mainGamePlayer SET cash = ?, lastOnline = ? WHERE name = 'Nick'";
    sqlite3_prepare(db, sqlSelect.c_str(), sqlSelect.size(), &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, mainPlayer.cash);
    sqlite3_bind_int(stmt, 2, mainPlayer.lastOnline);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    sqlSelect = "UPDATE dataMining SET perClick = ?, passive = ?  WHERE name = 'Nick'";         
    sqlite3_prepare(db, sqlSelect.c_str(), sqlSelect.size(), &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, mainPlayer.perClick);
    sqlite3_bind_int(stmt, 2, mainPlayer.passive);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    //cout<<mainPlayer.lastOnline<<endl;
   }
    
