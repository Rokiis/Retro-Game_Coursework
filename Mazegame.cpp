//group D2 - Hazar
#include <ncurses.h> 
#include <iostream>
#include <string>
#include <algorithm>
#include "sqlite3.h"
#include <ctime>
using namespace std;

bool mazeGameLoop = false;
    void printMiddle(WINDOW * win, int y, int x, int upDown, string asd) 
{
	int getLength = asd.length();									 
	int newY = (y / 2) - upDown;
	int newX = (x - getLength) / 2;
	mvwprintw(win, newY, newX, asd.c_str());
}

int main()
{
    while (!mazeGameLoop) 
    {
        
        initscr();
        cbreak();
        curs_set(0);
        noecho();
        int height, width, start_y, start_x;//create variables with int data type
        height = 20;//assign different numbers to each variable
        width = 70;
        start_y = 1;
        start_x = 1;
        
        WINDOW * mazeWin = newwin(height, width, start_y, start_x); //This is used to create a window. using assigned numbers to variables.
        refresh();
        wborder(mazeWin, 0, 0, 0, 0, 0, 0, 0, 0); //used to create a border around the window
        wrefresh(mazeWin);//refreshs a certain specified window.
        keypad(mazeWin, true);//enables the use of the keyboard
        
        string mazeMenu[2] = {"Continue", "Quit"};//create list with certain name
        int mazeChoice; //create variable with int datatype
        int mazeHighlight = 0; //create variable with int datatype and 0 inside it
        
        while(1)
        {
            for (int i = 0; i < 2; i++)
            {
                if (i == mazeHighlight)
                    wattron(mazeWin, A_REVERSE); //turns on attribute
                mvwprintw(mazeWin, i+7, 3, mazeMenu[i].c_str()); //this allows the list created earlier to be printed on the screen at specified location.
                wattroff(mazeWin, A_REVERSE);  //turns off attribute
            }
            mazeChoice = wgetch(mazeWin);
            
            switch(mazeChoice)  //using switch statement to enable the user to use the arrow 
            {
                case KEY_UP:
                    mazeHighlight--;
                    if(mazeHighlight == -1)
                        mazeHighlight = 1; //used to enable the up arrow key and if the highlight goes above the first value then it goes to the bottom value
                    break;
                case KEY_DOWN:
                    mazeHighlight++;
                    if(mazeHighlight == 2)
                        mazeHighlight = 0; //used to enable the down arrow key and if the highlight goes below the bottom value then it goes to the top.
                    break;
                default:
                    break;
            }
            if (mazeChoice == 10) //if the user press enter key it breaks
                break;
        }
        string mazeGameMenu = mazeMenu [mazeHighlight]; //creates a string variable with values of mainmenu list
        wrefresh(mazeWin); //refresh the mazeWin so that everything appears correctly.
        if (mazeGameMenu == "Continue") //if the user selects the option continue, then it goes to the next screen.
        {
            bool mazeGameLoop = false; //creates a bool with the a false value inside it
            while(!mazeGameLoop) //while the bool is not its value, it runs its code,, it basically runs the code below while its true
            {
                wrefresh(mazeWin);
                WINDOW * mazeIntroWin = newwin(20, 70, 1, 1);
                keypad(mazeIntroWin, true);
                refresh();
                wborder(mazeIntroWin, 0, 0, 0, 0, 0, 0, 0, 0);
                int mazeMaxY, mazeMaxX;
                getmaxyx(mazeIntroWin, mazeMaxY, mazeMaxX);//gets the max y and x coordinates
                printMiddle(mazeIntroWin, mazeMaxY, mazeMaxX, 9, "Instructions");//prints the text in the centre of the screen
                wrefresh(mazeIntroWin);
                string message1 = "Find your way through the firewall. Dont run into any traps";//saves a string into a variable
                mvwprintw(mazeIntroWin, 4, 2, "%s", message1.c_str());//used to print the string or contents of string at certain location on the screen
                wrefresh(mazeIntroWin);

                
                bool enterGameLoop = false; //This Is Room1
                while(!enterGameLoop) //same as bool and loop before
                {
                    wrefresh(mazeIntroWin);
                    WINDOW * mazeGameWin = newwin(20, 70, 1, 1);//same as before
                    refresh();
                    wborder(mazeGameWin, 0, 0, 0, 0, 0, 0, 0, 0);
                    keypad(mazeGameWin, true);
                    wrefresh(mazeGameWin);
                    int gameMaxY, gameMaxX;
                    getmaxyx(mazeGameWin, gameMaxY, gameMaxX);
                    printMiddle(mazeGameWin, gameMaxY, gameMaxX, 9, "Room1");
                    wrefresh(mazeGameWin);
                    string firstChoices[2] = {"Up", "Right"}; //same as before
                    int oneChoice;
                    int oneHighlight = 0;
                    
                    while(1)
                    {
                        for (int t = 0; t < 2; t++)
                        {
                            if (t == oneHighlight)
                                wattron(mazeGameWin, A_REVERSE);
                            mvwprintw(mazeGameWin, t+7, 3, firstChoices[t].c_str());
                            wattroff(mazeGameWin, A_REVERSE);
                        }
                        oneChoice = wgetch(mazeGameWin);

                        switch(oneChoice)
                        {
                            case KEY_UP:
                                oneHighlight--;
                                if(oneHighlight == -1)
                                    oneHighlight = 1;
                                break;
                            case KEY_DOWN:
                                oneHighlight++;
                                if(oneHighlight == 2)
                                    oneHighlight = 0;
                                break;
                            default:
                                break;
                        }
                        if (oneChoice == 10)
                            break;
                    }
                    string secondRoom = firstChoices [oneHighlight]; //This is room 2
                    wrefresh(mazeGameWin);
                    if (secondRoom == "Right")
                    {
                        bool secondBool = false;
                        while(!secondBool)
                        {
                            wrefresh(mazeGameWin);
                            WINDOW * secondWin = newwin(20, 70, 1, 1);
                            refresh();
                            wborder(secondWin, 0, 0, 0, 0, 0, 0, 0, 0);
                            keypad(secondWin, true);
                            int secondMaxY, secondMaxX;
                            getmaxyx(secondWin, secondMaxY, secondMaxX);
                            printMiddle(secondWin, secondMaxY, secondMaxX, 9, "Welcome to Room2");
                            wrefresh(secondWin);
                            string secondChoices[2] = {"Up", "Right"};
                            int twoChoice;
                            int twoHighlight = 0;
                            
                            while(1)
                            {
                                for(int r = 0; r < 2; r++)
                                {
                                    if(r == twoHighlight)
                                        wattron(secondWin, A_REVERSE);
                                    mvwprintw(secondWin, r+7, 3, secondChoices[r].c_str());
                                    wattroff(secondWin, A_REVERSE);
                                }
                                twoChoice = wgetch(secondWin);
                                
                                switch(twoChoice)
                                {
                                    case KEY_UP:
                                        twoHighlight--;
                                        if(twoHighlight == -1)
                                            twoHighlight = 1;
                                        break;
                                    case KEY_DOWN:
                                        twoHighlight++;
                                        if(twoHighlight == 2)
                                            twoHighlight = 0;
                                        break;
                                    default:
                                        break;
                                }
                                if (twoChoice == 10)
                                    break;
                            }
                            string thirdRoom = secondChoices [twoHighlight]; //This is room 3
                            wrefresh(secondWin);
                            if(thirdRoom == "Up")
                            {
                                bool thirdBool = false;
                                while(!thirdBool)
                                {
                                    wrefresh(secondWin);
                                    WINDOW * thirdWin = newwin(20, 70, 1, 1);
                                    refresh();
                                    wborder(thirdWin, 0, 0, 0, 0, 0, 0, 0, 0);
                                    keypad(thirdWin, true);
                                    int thirdMaxY, thirdMaxX;
                                    getmaxyx(thirdWin, thirdMaxY, thirdMaxX);
                                    printMiddle(thirdWin, thirdMaxY, thirdMaxX, 9, "Welcome to Room3");
                                    wrefresh(thirdWin);
                                    string thirdChoices[3] = {"Left", "Up", "Right"};
                                    int threeChoice;
                                    int threeHighlight = 0;
                                    
                                    while(1)
                                    {
                                        for(int w = 0; w < 3; w++)
                                        {
                                            if(w == threeHighlight)
                                                wattron(thirdWin, A_REVERSE);
                                            mvwprintw(thirdWin, w+7, 3, thirdChoices[w].c_str());
                                            wattroff(thirdWin, A_REVERSE);
                                        }
                                        threeChoice = wgetch(thirdWin);

                                        switch(threeChoice)
                                        {
                                            case KEY_UP:
                                                threeHighlight--;
                                                if(threeHighlight == -1)
                                                    threeHighlight = 2;
                                                break;
                                            case KEY_DOWN:
                                                threeHighlight++;
                                                if(threeHighlight == 3)
                                                    threeHighlight = 0;
                                                break;
                                            default:
                                                break;
                                        }
                                        if (threeChoice == 10)
                                            break;
                                    }
                                    string fourRoom = thirdChoices [threeHighlight]; //This is room 4
                                    wrefresh(thirdWin);
                                    if (fourRoom == "Right")
                                    {
                                        bool fourBool = false;
                                        while(!fourBool)
                                        {
                                            wrefresh(thirdWin);
                                            WINDOW * fourthWin = newwin(20, 70, 1, 1);
                                            refresh();
                                            wborder(fourthWin, 0, 0, 0, 0, 0, 0, 0, 0);
                                            keypad(fourthWin, true);
                                            int fourthMaxY, fourthMaxX;
                                            getmaxyx(fourthWin, fourthMaxY, fourthMaxX);
                                            printMiddle(fourthWin, fourthMaxY, fourthMaxX, 9, "Welcome to Room4");
                                            wrefresh(fourthWin);
                                            string fourthChoices[3] = {"Up", "Right", "Down"};
                                            int fourChoice;
                                            int fourHighlight = 0;
                                            
                                            while(1)
                                            {
                                                for (int x = 0; x < 3; x++)
                                                {
                                                    if(x == fourHighlight)
                                                        wattron(fourthWin, A_REVERSE);
                                                    mvwprintw(fourthWin, x+7, 3, fourthChoices[x].c_str());
                                                    wattroff(fourthWin, A_REVERSE);
                                                }
                                                fourChoice = wgetch(fourthWin);
                                                
                                                switch(fourChoice)
                                                {
                                                    case KEY_UP:
                                                        fourHighlight--;
                                                        if(fourHighlight == -1)
                                                            fourHighlight = 2;
                                                        break;
                                                    case KEY_DOWN:
                                                        fourHighlight++;
                                                        if(fourHighlight == 3)
                                                            fourHighlight = 0;
                                                        break;
                                                    default:
                                                        break;
                                                }
                                                if (fourChoice == 10)
                                                    break;
                                            }
                                            string fiveRoom = fourthChoices [fourHighlight]; //This is room 5
                                            wrefresh(fourthWin);
                                            if(fiveRoom == "Down")
                                            {
                                                bool fiveBool = false;
                                                while(!fiveBool)
                                                {
                                                    wrefresh(fourthWin);
                                                    WINDOW * fifthWin = newwin(20, 70, 1, 1);
                                                    refresh();
                                                    wborder(fifthWin, 0, 0, 0, 0, 0, 0, 0, 0);
                                                    keypad(fifthWin, true);
                                                    int fifthMaxY, fifthMaxX;
                                                    getmaxyx(fifthWin, fifthMaxY, fifthMaxX);
                                                    printMiddle(fifthWin, fifthMaxY, fifthMaxX, 9, "Welcome to Room5");
                                                    wrefresh(fifthWin);
                                                    string fifthChoices[2] = {"Up", "Right"};
                                                    int fiveChoice;
                                                    int fiveHighlight = 0;
                                                    
                                                    while(1)
                                                    {
                                                        for(int v = 0; v < 2; v++)
                                                        {
                                                            if(v == fiveHighlight)
                                                                wattron(fifthWin, A_REVERSE);
                                                            mvwprintw(fifthWin, v+7, 3, fifthChoices[v].c_str());
                                                            wattroff(fifthWin, A_REVERSE);
                                                        }
                                                        fiveChoice = wgetch(fifthWin);
                                                        
                                                        switch(fiveChoice)
                                                        {
                                                            case KEY_UP:
                                                                fiveHighlight--;
                                                                if(fiveHighlight == -1)
                                                                    fiveHighlight = 1;
                                                                break;
                                                            case KEY_DOWN:
                                                                fiveHighlight++;
                                                                if(fiveHighlight == 2)
                                                                    fiveHighlight = 0;
                                                                break;
                                                            default:
                                                                break;
                                                        }
                                                        if (fiveChoice == 10)
                                                            break;
                                                    }
                                                    string sixRoom = fifthChoices [fiveHighlight]; //This is room 6
                                                    wrefresh(fifthWin);
                                                    if(sixRoom == "Right")
                                                    {
                                                        bool sixBool = false;
                                                        while(!sixBool)
                                                        {
                                                            wrefresh(fifthWin);
                                                            WINDOW * sixthWin = newwin(20, 70, 1, 1);
                                                            refresh();
                                                            wborder(sixthWin, 0, 0, 0, 0, 0, 0, 0, 0);
                                                            keypad(sixthWin, true);
                                                            int sixthMaxY, sixthMaxX;
                                                            getmaxyx(sixthWin, sixthMaxY, sixthMaxX);
                                                            printMiddle(sixthWin, sixthMaxY, sixthMaxX, 9, "Welcome to Room6");
                                                            wrefresh(sixthWin);
                                                            string sixthChoices[3] = {"Left", "Up", "Right"};
                                                            int sixChoice;
                                                            int sixHighlight = 0;
                                                            
                                                            while(1)
                                                            {
                                                                for(int b = 0; b < 3; b++)
                                                                {
                                                                    if(b == sixHighlight)
                                                                        wattron(sixthWin, A_REVERSE);
                                                                    mvwprintw(sixthWin, b+7, 3, sixthChoices[b].c_str());
                                                                    wattroff(sixthWin, A_REVERSE);
                                                                }
                                                                sixChoice = wgetch(sixthWin);
                                                                
                                                                switch(sixChoice)
                                                                {
                                                                    case KEY_UP:
                                                                        sixHighlight--;
                                                                        if(sixHighlight == -1)
                                                                            sixHighlight = 2;
                                                                        break;
                                                                    case KEY_DOWN:
                                                                        sixHighlight++;
                                                                        if(sixHighlight == 3)
                                                                            sixHighlight = 0;
                                                                        break;
                                                                    default:
                                                                        break;
                                                                }
                                                                if (sixChoice == 10)
                                                                    break;
                                                            }
                                                            string sevenRoom = sixthChoices [sixHighlight]; // This is room 7
                                                            wrefresh(sixthWin);
                                                            if(sevenRoom == "Up")
                                                            {
                                                                bool sevenBool = false;
                                                                while(!sevenBool)
                                                                {
                                                                    wrefresh(sixthWin);
                                                                    WINDOW * seventhWin = newwin(20, 70, 1, 1);
                                                                    refresh();
                                                                    wborder(seventhWin, 0, 0, 0, 0, 0, 0, 0, 0);
                                                                    keypad(seventhWin, true);
                                                                    int seventhMaxY, seventhMaxX;
                                                                    getmaxyx(seventhWin, seventhMaxY, seventhMaxX);
                                                                    printMiddle(seventhWin, seventhMaxY, seventhMaxX, 9, "Welcome to Room7");
                                                                    wrefresh(seventhWin);
                                                                    string seventhChoices[3] = {"Left", "Up", "Right"};
                                                                    int sevenChoice;
                                                                    int sevenHighlight = 0;
                                                                    
                                                                    while(1)
                                                                    {
                                                                        for(int n = 0; n < 3; n++)
                                                                        {
                                                                            if(n == sevenHighlight)
                                                                                wattron(seventhWin, A_REVERSE);
                                                                            mvwprintw(seventhWin, n+7, 3, seventhChoices[n].c_str());
                                                                            wattroff(seventhWin, A_REVERSE);
                                                                        }
                                                                        sevenChoice = wgetch(seventhWin);
                                                                        
                                                                        switch(sevenChoice)
                                                                        {
                                                                            case KEY_UP:
                                                                                sevenHighlight--;
                                                                                if(sevenHighlight == -1)
                                                                                    sevenHighlight = 2;
                                                                                break;
                                                                            case KEY_DOWN:
                                                                                sevenHighlight++;
                                                                                if(sevenHighlight == 3)
                                                                                    sevenHighlight = 0;
                                                                                break;
                                                                            default:
                                                                                break;
                                                                        }
                                                                        if (sevenChoice == 10)
                                                                            break;
                                                                    }
                                                                    string eightRoom = seventhChoices [sevenHighlight]; //This is Room 8
                                                                    wrefresh(seventhWin);
                                                                    if(eightRoom == "Up")
                                                                    {
                                                                        wrefresh(seventhWin);
                                                                        WINDOW * eighthWin = newwin(20, 70, 1, 1);
                                                                        refresh();
                                                                        wborder(eighthWin, 0, 0, 0, 0, 0, 0, 0, 0);
                                                                        keypad(eighthWin, true);
                                                                        int eighthMaxY, eighthMaxX;
                                                                        getmaxyx(eighthWin, eighthMaxY, eighthMaxX);
                                                                        printMiddle(eighthWin, eighthMaxY, eighthMaxX, 9, "Welcome to Room8");
                                                                        wrefresh(eighthWin);
                                                                        string eighthChoices[3] = {"Left", "Up", "RIGHT"};
                                                                        int eightChoice;
                                                                        int eightHighlight = 0;
                                                                        
                                                                        while(1)
                                                                        {
                                                                            for(int k = 0; k < 3; k++)
                                                                            {
                                                                                if(k == eightHighlight)
                                                                                    wattron(eighthWin, A_REVERSE);
                                                                                mvwprintw(eighthWin, k+7, 3, eighthChoices[k].c_str());
                                                                                wattroff(eighthWin, A_REVERSE);
                                                                            }
                                                                            eightChoice = wgetch(eighthWin);
                                                                            
                                                                            switch(eightChoice)
                                                                            {
                                                                                case KEY_UP:
                                                                                    eightHighlight--;
                                                                                    if(eightHighlight == -1)
                                                                                        eightHighlight = 2;
                                                                                    break;
                                                                                case KEY_DOWN:
                                                                                    eightHighlight++;
                                                                                    if(eightHighlight == 3)
                                                                                        eightHighlight = 0;
                                                                                    break;
                                                                                default:
                                                                                    break;
                                                                            }
                                                                            if (eightChoice == 10)
                                                                                break;
                                                                        }
                                                                        string nineRoom = eighthChoices [eightHighlight];
                                                                        wrefresh(eighthWin);
                                                                        if(nineRoom == "Left")
                                                                        {
                                                                            bool nineBool = false;
                                                                            while(!nineBool)
                                                                            {
                                                                                wrefresh(eighthWin);
                                                                                WINDOW * ninthWin = newwin(20, 70, 1, 1);
                                                                                refresh();
                                                                                wborder(ninthWin, 0, 0, 0, 0, 0, 0, 0, 0);
                                                                                wrefresh(ninthWin);
                                                                                keypad(ninthWin, true);
                                                                                int ninthMaxY, ninthMaxX;
                                                                                getmaxyx(ninthWin, ninthMaxY, ninthMaxX);
                                                                                printMiddle(ninthWin, ninthMaxY, ninthMaxX, 9, "You have successfuly broke through the firewall");
                                                                                wrefresh(ninthWin);
                                                                                string ninthChoices[1] = {"MainMenu"};
                                                                                int nineChoice;
                                                                                int nineHighlight = 0;
                                                                                
                                                                                while(1)
                                                                                {
                                                                                    for(int g = 0; g < 1; g++)
                                                                                    {
                                                                                        if(g == nineHighlight)
                                                                                            wattron(ninthWin, A_REVERSE);
                                                                                        mvwprintw(ninthWin, g+7, 3, ninthChoices[g].c_str());
                                                                                        wattroff(ninthWin, A_REVERSE);
                                                                                    }
                                                                                    nineChoice = wgetch(ninthWin);
                                                                                    
                                                                                    switch(nineChoice)
                                                                                    {
                                                                                        case KEY_UP:
                                                                                            nineHighlight--;
                                                                                            if(nineHighlight == -1)
                                                                                                nineHighlight = 0;
                                                                                            break;
                                                                                        case KEY_DOWN:
                                                                                            nineHighlight++;
                                                                                            if(nineHighlight == 1)
                                                                                                nineHighlight = 0;
                                                                                            break;
                                                                                        default:
                                                                                            break;
                                                                                    }
                                                                                    if(nineChoice == "MainMenu")
                                                                                        break;
                                                                                }
                                                                                
                                                                            }
                                                                        }
                                                                    }
                                                                    string eightRoom2 = seventhChoices [sevenHighlight]; //End Game room8
                                                                    wrefresh(seventhWin);                    
                                                                    if (eightRoom2 == "Left", "Right")
                                                                    {
                                                                        bool eightRoomBool = false;
                                                                        while(!eightRoomBool)
                                                                        {
                                                                            wrefresh(seventhWin);
                                                                            WINDOW * deadWin7 = newwin(20, 70, 1, 1);
                                                                            wborder(deadWin7, 0, 0, 0, 0, 0, 0, 0, 0);
                                                                            wrefresh(deadWin7);
                                                                            string message8 = "You Ran Into A trap,  They know your in their system";
                                                                            string message8b = "Your just about in their system, You have 150 points";
                                                                            mvwprintw(deadWin7, 4, 2, "%s", message8.c_str());
                                                                            mvwprintw(deadWin7, 4, 2, "%s", message8b.c_str());
                                                                            wrefresh(deadWin7);
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                            string sevenRoom2 = sixthChoices [sixHighlight]; //End Game room7
                                                            wrefresh(sixthWin);                    
                                                            if (sevenRoom2 == "Left", "Right")
                                                            {
                                                                bool sevenRoomBool = false;
                                                                while(!sevenRoomBool)
                                                                {
                                                                    wrefresh(sixthWin);
                                                                    WINDOW * deadWin6 = newwin(20, 70, 1, 1);
                                                                    wborder(deadWin6, 0, 0, 0, 0, 0, 0, 0, 0);
                                                                    wrefresh(deadWin6);
                                                                    string message7 = "You Ran Into A trap, They know your in their system";
                                                                    string message7b = "Your just about in their system, You have 150 points";
                                                                    mvwprintw(deadWin6, 4, 2, "%s", message7.c_str());
                                                                    mvwprintw(deadWin6, 5, 2, "%s", message7b.c_str());
                                                                    wrefresh(deadWin6);
                                                                }
                                                            }
                                                        }
                                                    }
                                                    string sixRoom2 = fifthChoices [fiveHighlight]; //End Game room6
                                                    wrefresh(fifthWin);                    
                                                    if (sixRoom2 == "Up")
                                                    {
                                                        bool sixRoomBool = false;
                                                        while(!sixRoomBool)
                                                        {
                                                            wrefresh(fifthWin);
                                                            WINDOW * deadWin5 = newwin(20, 70, 1, 1);
                                                            wborder(deadWin5, 0, 0, 0, 0, 0, 0, 0, 0);
                                                            wrefresh(deadWin5);
                                                            string message6 = "You Ran Into A trap, They know your in their system";
                                                            string message6b = "Your just about in their system, You have 80 points";
                                                            mvwprintw(deadWin5, 4, 2, "%s", message6.c_str());
                                                            mvwprintw(deadWin5, 5, 2, "%s", message6b.c_str());
                                                            wrefresh(deadWin5);
                                                        }
                                                    }
                                                }
                                            }
                                            string fiveRoom2 = fourthChoices [fourHighlight]; //End Game Room5
                                            wrefresh(fourthWin);                    
                                            if (fiveRoom2 == "Right", "Up")
                                            {
                                                bool fiveRoomBool = false;
                                                while(!fiveRoomBool)
                                                {
                                                    wrefresh(fourthWin);
                                                    WINDOW * deadWin4 = newwin(20, 70, 1, 1);
                                                    wborder(deadWin4, 0, 0, 0, 0, 0, 0, 0, 0);
                                                    wrefresh(deadWin4);
                                                    string message5 = "You Ran Into A trap, They know your in their system";
                                                    string message5b = "Your just about in their system, You have 40 points";
                                                    mvwprintw(deadWin4, 4, 2, "%s", message5.c_str());
                                                    mvwprintw(deadWin4, 5, 2, "%s", message5b.c_str());
                                                    wrefresh(deadWin4);
                                                }
                                            }
                                        }
                                    }
                                    string fourthRoom2 = thirdChoices [threeHighlight]; // End Game Room4
                                    wrefresh(thirdWin);                    
                                    if (fourthRoom2 == "Left", "Up")
                                    {
                                        bool fourRoomBool = false;
                                        while(!fourRoomBool)
                                        {
                                            wrefresh(thirdWin);
                                            WINDOW * deadWin3 = newwin(20, 70, 1, 1);
                                            wborder(deadWin3, 0, 0, 0, 0, 0, 0, 0, 0);
                                            wrefresh(deadWin3);
                                            string message4 = "You Ran Into A trap, They know your in their system";
                                            string message4b = "You didnt get far into their system, You acquired 25 points";
                                            mvwprintw(deadWin3, 4, 2, "%s", message4.c_str());
                                            mvwprintw(deadWin3, 5, 2, "%s", message4b.c_str());
                                            wrefresh(deadWin3);
                                            
                                        }
                                    }
                                }
                            }
                            string thirdRoom2 = secondChoices [twoHighlight]; // End Game Room3
                            wrefresh(secondWin);                    
                            if (thirdRoom2 == "Right")
                            {
                                bool thirdRoomBool = false;
                                while(!thirdRoomBool)
                                {
                                    wrefresh(secondWin);
                                    WINDOW * deadWin2 = newwin(20, 70, 1, 1);
                                    wborder(deadWin2, 0, 0, 0, 0, 0, 0, 0, 0);
                                    wrefresh(deadWin2);
                                    string message3 = "You Ran Into A trap, They know your in their system";
                                    string message3b = "You barely went into their system, You get only 10 Points";
                                    mvwprintw(deadWin2, 4, 2, "%s", message3.c_str());
                                    mvwprintw(deadWin2, 5, 2, "%s", message3b.c_str());
                                    wrefresh(deadWin2);
                                }
                            }
                        }
                    }
                    string secondRoom2 = firstChoices [oneHighlight]; //End Game Room2
                    wrefresh(mazeGameWin);                    
                    if (secondRoom2 == "Up")
                    {
                        bool secondBool2 = false;
                        while(!secondBool2)
                        {
                            wrefresh(mazeGameWin);
                            WINDOW * deadWin1 = newwin(20, 70, 1, 1);
                            wborder(deadWin1, 0, 0, 0, 0, 0, 0, 0, 0);
                            string message2 = "You Ran Into A trap,  They know your in their system";
                            string message2b = "Your Scored 0 Points";
                            mvwprintw(deadWin1, 4, 2, "%s", message2.c_str());
                            mvwprintw(deadWin1, 5, 2, "%s", message2b.c_str());
                            wrefresh(deadWin1);
                        }
                    }
                }
            }
        }
    }
    getch();
    endwin();
    
    return 0;    
} 
