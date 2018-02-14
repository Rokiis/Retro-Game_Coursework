#include <iostream>
#include <ncurses.h>
#include <string>
#include <algorithm>
using namespace std;
bool inboxLoop = false;
    void printMiddle(WINDOW * win, int y, int x, int upDown, string asd) 
{
	int getLength = asd.length();									 
	int newY = (y / 2) - upDown;
	int newX = (x - getLength) / 2;
	mvwprintw(win, newY, newX, asd.c_str());
}
int main()
{
    while(!inboxLoop)
    {
        initscr();
        noecho();
        curs_set(0);
        start_color();
        WINDOW * inboxMenu = newwin(20, 70 , 1 , 1);
        refresh();
        wborder(inboxMenu, 0 , 0 , 0 , 0 , 0 , 0 , 0, 0);
        string inboxTitle = "Inbox";
        int inboxMaxY, inboxMaxX;
        getmaxyx(inboxMenu, inboxMaxY, inboxMaxX);
        
        init_pair(1, COLOR_GREEN, 0);
		init_pair(69, COLOR_RED, 0);	//colour initialisations
		init_pair(2, COLOR_CYAN, 0);
		init_pair(3, COLOR_MAGENTA, 0);
		init_pair(4, COLOR_WHITE, 0);
		init_pair(5, COLOR_YELLOW, 0);
        
        wattron(inboxMenu, COLOR_PAIR(1));
        printMiddle(inboxMenu, inboxMaxY, inboxMaxX, 9, inboxTitle);
        wattroff(inboxMenu, COLOR_PAIR(1));
        
        wattron(inboxMenu, COLOR_PAIR(2));
        keypad(inboxMenu, true);
        string inboxMenuOptions[4] = {"Email 1", "Email 2", "Email 3","Exit"};
        int inboxMenuChoice;
        int inboxMenuHighlight = 0;
        while(1)
        {
            for(int i = 0; i < 4; i++)
            {
                if( i == inboxMenuHighlight)
                    wattron(inboxMenu, A_STANDOUT);
                mvwprintw(inboxMenu, 5*i + 3, 3, inboxMenuOptions[i].c_str());
                wattroff(inboxMenu, A_STANDOUT); 
                if(inboxMenuOptions[i] != "Exit")
                {
                    string name = "MR. STONE";
                    whline(inboxMenu,ACS_HLINE,20);
                    //wattron(inboxMenu,COLOR_PAIR(69));
                    whline(inboxMenu,ACS_DIAMOND,i+1);
                    //wattroff(inboxMenu,COLOR_PAIR(69));
                    //whline(inboxMenu,ACS_DIAMOND,21);
                    mvwprintw(inboxMenu,(5*i + 3)+1, 3, "Sender: %s",name.c_str());
                    mvwprintw(inboxMenu,(5*i + 3)+2, 3, "Subject: ");
                    mvwprintw(inboxMenu,(5*i + 3)+3, 3, "Reward:");
                }   
            }
            inboxMenuChoice = wgetch(inboxMenu);
            switch(inboxMenuChoice)
            {
                case KEY_UP:
                    inboxMenuHighlight--;
                    if(inboxMenuHighlight == -1)
                        inboxMenuHighlight = 3;
                    break;
                case KEY_DOWN:
                    inboxMenuHighlight++;
                    if(inboxMenuHighlight == 4)
                        inboxMenuHighlight = 0;
                    break;
                default:
                    break;
            }
            if(inboxMenuChoice == 10)
                break;
            string inboxMenuInput = inboxMenuOptions[inboxMenuHighlight];
            wrefresh(inboxMenu);
            if(inboxMenuInput == "Exit")
            {
                inboxLoop = true;
            }
            refresh();
            
        }
    }
    endwin();
}
