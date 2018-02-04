#include <ncurses.h> // or #include <ncurses.h> (linux) sudo apt-get install libncurses5-dev libncursesw5-dev
#include <iostream>
#include <string>
using namespace std;
bool mainMenuLoop = false;
void printMiddle(WINDOW * win, int y, int x, int upDown, string asd) //function I created to print text within a window at the centre. aesthetics n shit. 
{
	int getLength = asd.length();									 //int upDown is buggy. 9 = top of screen, play around with it. 
	int newY = (y / 2) - upDown;
	int newX = (x - getLength) / 2;
	mvwprintw(win, newY, newX, asd.c_str());
}
int main()
{
	while (!mainMenuLoop)
	{
		initscr();
		noecho(); //turns off showing what key the user pressed
		start_color(); //enables colours 
		int height, width, start_y, start_x;
		height = 20;
		width = 70;
		start_y = 1;
		start_x = 1;

		WINDOW * mainMenu = newwin(height, width, start_y, start_x); //create window
		refresh(); //refresh screen to allow window

				   //box(win, 0, 0); //create box, takes characters to form box edges e.g char c = 'g'; box(win, (int)c, 0);
		int left, right, top, bottom, tlc, trc, blc, brc;
		/*char lr = '|';
		char corners = '+';			//used for setting specific characters for border
		char tb = '-';*/
		left = right = 0;
		top = bottom = 0;
		tlc = trc = blc = brc = 0;
		wborder(mainMenu, left, right, top, bottom, tlc, trc, blc, brc); //creates border (aka box) around window, more efficient than box command
		
		string stux1 = " SSS  TTTTTT U   U X   X  N   N EEEE TTTTTT";
		string stux2 = "S       TT   U   U  X X   NN  N E      TT  ";
		string stux3 = " SSS    TT   U   U   X    N N N EEE    TT  ";					//won't work on codio, works on win10 vis 2017 with pdcurses
		string stux4 = "    S   TT   U   U  X X   N  NN E      TT  ";
		string stux5 = "SSSS    TT    UUU  X   X  N   N EEEE   TT  ";
		int mainMaxY, mainMaxX;
		getmaxyx(mainMenu, mainMaxY, mainMaxX);

		init_pair(1, COLOR_GREEN, 0);
    init_pair(69, COLOR_RED, 0);
    init_pair(2, COLOR_CYAN, 0);
		wattron(mainMenu, COLOR_PAIR(1));
	
		printMiddle(mainMenu, mainMaxY, mainMaxX, 9, stux1);
		printMiddle(mainMenu, mainMaxY, mainMaxX, 8, stux2);
		printMiddle(mainMenu, mainMaxY, mainMaxX, 7, stux3);
		printMiddle(mainMenu, mainMaxY, mainMaxX, 6, stux4);
		printMiddle(mainMenu, mainMaxY, mainMaxX, 5, stux5);
    wattroff(mainMenu, COLOR_PAIR(1));
    
    wattron(mainMenu, COLOR_PAIR(69));
		mvwprintw(mainMenu, 6, 22, "Stuxnet V1.0 - Group D2");
    wattroff(mainMenu, COLOR_PAIR(69));
		wattron(mainMenu, COLOR_PAIR(2));
    
		wrefresh(mainMenu); //refreshes specfic window
		keypad(mainMenu, true);			//must be enabled for usage of arrow keys (see below)
		string mainMenuChoices[3] = { "PLAY GAME", "INSTRUCTIONS", "EXIT" };			//strings used to form options of selection 
		int mainMenuChoice;
		int mainMenuHighlight = 0;
		while (1)				//while loop so that unless conditions are met, choice must be made
		{
			for (int i = 0; i < 3; i++)
			{
				if (i == mainMenuHighlight)
					wattron(mainMenu, A_REVERSE);
				mvwprintw(mainMenu, i + 7, 3, mainMenuChoices[i].c_str()); //.c_str is so useful, allows you to convert string into const char * format
				wattroff(mainMenu, A_REVERSE);
			}
			mainMenuChoice = wgetch(mainMenu);
			switch (mainMenuChoice)
			{
			case KEY_UP:
				mainMenuHighlight--;
				if (mainMenuHighlight == -1)
					mainMenuHighlight = 0;
				break;
			case KEY_DOWN:
				mainMenuHighlight++;
				if (mainMenuHighlight == 3)
					mainMenuHighlight = 2;
				break;
			default:
				break;
			}
			if (mainMenuChoice == 10)
				break;
		}
		
		string inputMainMenu = mainMenuChoices[mainMenuHighlight];
		wrefresh(mainMenu);
		if (inputMainMenu == "PLAY GAME")
		{
			bool characterCreationLoop = false;
			while (!characterCreationLoop)
			{
				wrefresh(mainMenu);
				WINDOW * characterCreation = newwin(20, 70, 1, 1);
				refresh();
				wborder(characterCreation, 0, 0, 0, 0, 0, 0, 0, 0);
				wattron(characterCreation, COLOR_PAIR(1));
				mvwprintw(characterCreation, 1, 30, "CHARACTER CREATION");
				wattroff(characterCreation, COLOR_PAIR(1));
				wattron(characterCreation, COLOR_PAIR(2));
				keypad(characterCreation, true);
				string characterCreationChoices[2] = { "ENTER YOUR NAME", "GO BACK" };
				int characterCreationChoice;
				int chacterCreationHighlight = 0;
				while (1)
				{
					for (int k = 0; k < 2; k++)
					{
						if (k == chacterCreationHighlight)
							wattron(characterCreation, A_REVERSE);
						mvwprintw(characterCreation, k + 7, 2, characterCreationChoices[k].c_str());
						wattroff(characterCreation, A_REVERSE);
					}
					characterCreationChoice = wgetch(characterCreation);
					switch (characterCreationChoice)
					{
					case KEY_UP:
						chacterCreationHighlight--;
						if (chacterCreationHighlight == -1)
							chacterCreationHighlight = 0;
						break;
					case KEY_DOWN:
						chacterCreationHighlight++;
						if (chacterCreationHighlight == 2)
							chacterCreationHighlight = 1;
						break;
					default:
						break;
					}
					if (characterCreationChoice == 10)
						break;
				}
				string inputCharacterCreation = characterCreationChoices[chacterCreationHighlight];
				wrefresh(characterCreation);
				if (inputCharacterCreation == "ENTER YOUR NAME")
				{
					echo();
					char playerSessionName[15];
					wrefresh(characterCreation);
					mvwprintw(characterCreation, 13, 2, "YOUR NAME:");
					mvwscanw(characterCreation, 14, 2, "%s", playerSessionName);
					wrefresh(characterCreation);
					noecho();
					mvwprintw(characterCreation, 14, 2, "YOUR NAME IS %s", playerSessionName);
					wrefresh(characterCreation);
					characterCreationLoop = true;
					getch();

				}
				if (inputCharacterCreation == "GO BACK")
				{
					characterCreationLoop = true;
					refresh();
				}
				wrefresh(characterCreation);
			}
		}
		if (inputMainMenu == "EXIT")
		{
			mainMenuLoop = true;
		}
		if (inputMainMenu == "INSTRUCTIONS")
		{
			bool howToPlayLoop = false;
			while (!howToPlayLoop)
			{
				wrefresh(mainMenu);
				WINDOW * howToPlay = newwin(20, 70, 1, 1);
				refresh();
				wborder(howToPlay, 0, 0, 0, 0, 0, 0, 0, 0);
				wattron(howToPlay, COLOR_PAIR(1));
				mvwprintw(howToPlay, 1, 30, "INSTRUCTIONS");
				int howToMaxY, howToMaxX;
				getmaxyx(howToPlay, howToMaxY, howToMaxX);
				string test = "instructions go here";
				/*int x = test.length();
				mvwprintw(howToPlay, howToMaxY/2, (howToMaxX-x)/2, test.c_str());*/
				printMiddle(howToPlay, howToMaxY, howToMaxX, 1, test);
				printMiddle(howToPlay, howToMaxY, howToMaxX, 2, test);
				printMiddle(howToPlay, howToMaxY, howToMaxX, 3, test);
				wattroff(howToPlay, COLOR_PAIR(1));
				wattron(howToPlay, COLOR_PAIR(2));
				keypad(howToPlay, true);
				string howToPlayChoices[1] = { "GO BACK" };
				int howToPlayChoice;
				int howToPlayHighlight = 0;
				while (1)
				{
					for (int k = 0; k < 1; k++)
					{
						if (k == howToPlayHighlight)
							wattron(howToPlay, A_REVERSE);
						mvwprintw(howToPlay, k + 7, 2, howToPlayChoices[k].c_str()); 
						wattroff(howToPlay, A_REVERSE);
					}
					howToPlayChoice = wgetch(howToPlay);
					switch (howToPlayChoice)
					{
					default:
						break;
					}
					if (howToPlayChoice == 10)
						break;
				}
				string inputCharacterCreation = howToPlayChoices[howToPlayHighlight];
				wrefresh(howToPlay);
				if (inputCharacterCreation == "GO BACK")
				{
					howToPlayLoop = true;
					refresh();
				}
				wrefresh(howToPlay);
			}
		}
		
	}

	return 0;
}
