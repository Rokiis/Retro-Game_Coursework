//d.jones
//group d2
#include "curses.h" // or #include <ncurses.h> (linux) sudo apt-get install libncurses5-dev libncursesw5-dev
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <time.h>
#include <vector>
#include <stdlib.h>


using namespace std;
bool mainMenuLoop = false;


typedef struct Position
{
	int x;
	int y;

} Position;
typedef struct Room
{
	Position position;
	int height;
	int width;

	Position ** doors; //door generation, 4 possible doors on buildings
					   //Enemy ** enemies;
					   //Item ** items;
}Room;
typedef struct DanielPlayer
{
	Position position;
	int health;
	int eloRating;
} DanielPlayer;

//map
Room ** mapSetup(WINDOW * window);

//player
DanielPlayer * playerSetup(WINDOW * win);
Position * handlePlayerInput(WINDOW * win, int input, DanielPlayer * DanielGamePlayer);
void checkPosition(WINDOW * win, Position * newPosition, DanielPlayer * DanielGamePlayer, char ** level);
void playerMove(WINDOW * win, Position * newPosition, DanielPlayer * DanielGamePlayer, char ** level);
//room
Room * createRoom(int y, int x, int height, int width);
void drawRoom(WINDOW * win, Room * room);
int doorPath(WINDOW * win, Position * doorOne, Position * doorTwo);

Position * handlePlayerInput(WINDOW * win, int input, DanielPlayer * DanielGamePlayer)
{

	Position * newPosition;
	newPosition = (Position *)malloc(sizeof(Position));
	switch (input)
	{
		//move up
	case KEY_UP:
	case 'w':
	case 'W':
		newPosition->y = DanielGamePlayer->position.y - 1;
		newPosition->x = DanielGamePlayer->position.x;
		break;
		//move down
	case KEY_DOWN:
	case 's':
	case 'S':
		newPosition->y = DanielGamePlayer->position.y + 1;
		newPosition->x = DanielGamePlayer->position.x;
		break;
		//move left
	case KEY_LEFT:
	case 'a':
	case 'A':
		newPosition->y = DanielGamePlayer->position.y;
		newPosition->x = DanielGamePlayer->position.x - 1;
		break;
		//move right
	case KEY_RIGHT:
	case 'd':
	case 'D':
		newPosition->y = DanielGamePlayer->position.y;
		newPosition->x = DanielGamePlayer->position.x + 1;
		break;
	default:
		break;
	}

	return newPosition;

}
Room ** mapSetup(WINDOW * window)
{
	Room ** rooms;
	rooms = (Room **)malloc(sizeof(Room) * 6);

	rooms[0] = createRoom(10, 40, 7, 11);
	drawRoom(window, rooms[0]);

	rooms[1] = createRoom(5, 5, 10, 11); //up/down, left/right, height, width
	drawRoom(window, rooms[1]);

	rooms[2] = createRoom(1, 50, 3, 10);
	drawRoom(window, rooms[2]);

	doorPath(window, rooms[1]->doors[3], rooms[0]->doors[1]);		//function to connect doors of rooms
	doorPath(window, rooms[2]->doors[2], rooms[0]->doors[0]);



	return rooms;
}

char ** saveLevelPositions(WINDOW * win)
{
	int x, y;
	char ** positions;
	positions = (char **)(malloc(sizeof(char *) * 25));

	for (y = 0; y < 25; y++)
	{
		positions[y] = (char *)malloc(sizeof(char) * 100);
		for (x = 0; x < 100; x++)
		{
			positions[y][x] = mvwinch(win, y, x);
		}
	}
	return positions;
}

Room * createRoom(int y, int x, int height, int width)
{
	Room * newRoom;
	newRoom = (Room *)malloc(sizeof(Room));
	newRoom->position.y = y;
	newRoom->position.x = x;
	newRoom->height = height;
	newRoom->width = width;


	newRoom->doors = (Position **)malloc(sizeof(Position) * 4);

	newRoom->doors[0] = (Position *)malloc(sizeof(Position));
	newRoom->doors[0]->x = rand() % (width - 2) + newRoom->position.x + 1;
	newRoom->doors[0]->y = newRoom->position.y;														//top door

	newRoom->doors[1] = (Position *)malloc(sizeof(Position));
	newRoom->doors[1]->y = rand() % (height - 2) + newRoom->position.y + 1;										//left door
	newRoom->doors[1]->x = newRoom->position.x;

	newRoom->doors[2] = (Position *)malloc(sizeof(Position));
	newRoom->doors[2]->x = rand() % (width - 2) + newRoom->position.x + 1;
	newRoom->doors[2]->y = newRoom->position.y + newRoom->height;										//bottom door

	newRoom->doors[3] = (Position *)malloc(sizeof(Position));
	newRoom->doors[3]->y = rand() % (height - 2) + newRoom->position.y + 1;										//right door
	newRoom->doors[3]->x = newRoom->position.x + width - 1;

	return newRoom;
}
void drawRoom(WINDOW * win, Room * room)
{
	int y;
	int x;
	//draw top and bottom of room
	wattron(win, COLOR_PAIR(1));
	for (x = room->position.x; x < room->position.x + room->width; x++)
	{
		mvwprintw(win, room->position.y, x, "#"); //top
		mvwprintw(win, room->position.y + room->height, x, "="); //bottom
	}
	wattroff(win, COLOR_PAIR(1));
	//draw floor / side
	for (y = room->position.y + 1; y < room->position.y + room->height; y++)
	{
		wattron(win, COLOR_PAIR(1));
		//side
		mvwprintw(win, y, room->position.x, "|");
		mvwprintw(win, y, room->position.x + room->width - 1, "|");
		//floor
		wattroff(win, COLOR_PAIR(1));
		for (x = room->position.x + 1; x < room->position.x + room->width - 1; x++)
		{
			mvwprintw(win, y, x, ".");
		}
	}
	//draw doors

	mvwprintw(win, room->doors[0]->y, room->doors[0]->x, "+");
	mvwprintw(win, room->doors[1]->y, room->doors[1]->x, "+");
	mvwprintw(win, room->doors[2]->y, room->doors[2]->x, "+");
	mvwprintw(win, room->doors[3]->y, room->doors[3]->x, "+");


}
int doorPath(WINDOW * win, Position * doorOne, Position * doorTwo)
{
	Position temp;
	Position previous;
	temp.x = doorOne->x;
	temp.y = doorOne->y;

	previous = temp;

	int count = 0;

	while (1)
	{
		//check left 
		if ((abs((temp.x - 1) - doorTwo->x) < abs(temp.x - doorTwo->x)) && (mvwinch(win, temp.y, temp.x - 1) == ' '))
		{
			previous.x = temp.x;
			temp.x = temp.x - 1;
		}
		//checks right
		else if ((abs((temp.x + 1) - doorTwo->x) < abs(temp.x - doorTwo->x)) && (mvwinch(win, temp.y, temp.x + 1) == ' '))
		{
			//mvwprintw(win, temp.y, temp.x + 1, "#");
			previous.x = temp.x;
			temp.x = temp.x + 1;
		}																																	//path finding algorithm
		//checks down																																	
		else if ((abs((temp.y + 1) - doorTwo->y) < abs(temp.y - doorTwo->y)) && (mvwinch(win, temp.y + 1, temp.x) == ' '))
		{
			previous.y = temp.y;
			temp.y = temp.y + 1;
		}
		//checks up
		else if ((abs((temp.y - 1) - doorTwo->y) < abs(temp.y - doorTwo->y)) && (mvwinch(win, temp.y - 1, temp.x) == ' '))
		{
			previous.y = temp.y;
			temp.y = temp.y - 1;
		}
		else
		{
			if (count == 0)
			{
				temp = previous;
				count++;
				continue;
			}
			else
			{
				return 0;
			}
		}
		mvwprintw(win, temp.y, temp.x, "#");

	}

	return 1;
}
void checkPosition(WINDOW * win, Position * newPosition, DanielPlayer * DanielGamePlayer, char ** level)
{
	int space;
	switch (mvwinch(win, newPosition->y, newPosition->x))		//checks character collision
	{
	case '.':
	case '#':
	case '+':
		playerMove(win, newPosition, DanielGamePlayer, level);			
		break;
	default:
		move(DanielGamePlayer->position.y, DanielGamePlayer->position.x);
		break;
	}

}
void playerMove(WINDOW * win, Position * newPosition, DanielPlayer * DanielGamePlayer, char ** level)
{
	char buffer[8];

	sprintf_s(buffer, "%c", level[DanielGamePlayer->position.y][DanielGamePlayer->position.x]);

	mvwprintw(win, DanielGamePlayer->position.y, DanielGamePlayer->position.x, buffer);

	DanielGamePlayer->position.y = newPosition->y;
	DanielGamePlayer->position.x = newPosition->x;
	wattron(win, COLOR_PAIR(5));																		//functions related to movement
	mvwprintw(win, DanielGamePlayer->position.y, DanielGamePlayer->position.x, "@");
	move(DanielGamePlayer->position.y, DanielGamePlayer->position.x);
	wattroff(win, COLOR_PAIR(5));

}
DanielPlayer * playerSetup(WINDOW * win)
{
	DanielPlayer * newPlayer;
	newPlayer = (DanielPlayer *)malloc(sizeof(DanielPlayer));

	newPlayer->position.y = 10;			//starting positions
	newPlayer->position.x = 13;
	newPlayer->health = 10;

	mvwprintw(win, newPlayer->position.y, newPlayer->position.x, "@");
	move(newPlayer->position.y, newPlayer->position.x);

	return newPlayer;
}
//functions below are for the main menu. above are for daniel's game. 


class MainGamePlayer
{
public:
	string name;
	int strikes;			//used for main menu stats only
	int cash;
};
void printMiddle(WINDOW * win, int y, int x, int upDown, string asd) //function I created to print text within a window at the centre.
{
	int getLength = asd.length();									 //int upDown is buggy. 9 = top of screen, play around with it. 
	int newY = (y / 2) - upDown;
	int newX = (x - getLength) / 2;
	mvwprintw(win, newY, newX, asd.c_str());
}



int main()
{
	srand(time(NULL)); //implement seed function

	while (!mainMenuLoop)
	{
		DanielPlayer * DanielGamePlayer;
		MainGamePlayer mainPlayer;
		initscr();
		curs_set(0);
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
		int instructionMaxY, instructionMaxX;
		getmaxyx(mainMenu, instructionMaxY, instructionMaxX);

		init_pair(1, COLOR_GREEN, 0);
		init_pair(69, COLOR_RED, 0);	//colour initialisations
		init_pair(2, COLOR_CYAN, 0);
		init_pair(3, COLOR_MAGENTA, 0);
		init_pair(4, COLOR_WHITE, 0);
		init_pair(5, COLOR_YELLOW, 0);
		init_pair(6, COLOR_WHITE, 4);



		wattron(mainMenu, COLOR_PAIR(1));
		printMiddle(mainMenu, instructionMaxY, instructionMaxX, 9, stux1);
		printMiddle(mainMenu, instructionMaxY, instructionMaxX, 8, stux2);
		printMiddle(mainMenu, instructionMaxY, instructionMaxX, 7, stux3);
		printMiddle(mainMenu, instructionMaxY, instructionMaxX, 6, stux4);
		printMiddle(mainMenu, instructionMaxY, instructionMaxX, 5, stux5);
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
		while (1)		    //while loop so that unless conditions are met, choice must be made
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
			case 'w':
			case KEY_UP:
				mainMenuHighlight--;
				if (mainMenuHighlight == -1)
					mainMenuHighlight = 2;
				break;
			case 's':
			case KEY_DOWN:
				mainMenuHighlight++;
				if (mainMenuHighlight == 3)
					mainMenuHighlight = 0;
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
				WINDOW * inboxMenu = newwin(20, 70, 1, 1);
				refresh();
				wborder(inboxMenu, 0, 0, 0, 0, 0, 0, 0, 0);
				wattron(inboxMenu, COLOR_PAIR(1));
				int creationMaxY, creationMaxX;
				getmaxyx(inboxMenu, creationMaxY, creationMaxX);
				printMiddle(inboxMenu, creationMaxY, creationMaxX, 9, "CHARACTER CREATION");
				wattroff(inboxMenu, COLOR_PAIR(1));
				wattron(inboxMenu, COLOR_PAIR(2));
				keypad(inboxMenu, true);
				string characterCreationChoices[2] = { "ENTER YOUR NAME", "GO BACK" };
				int characterCreationChoice;
				int characterCreationHighlight = 0;
				while (1)
				{
					for (int k = 0; k < 2; k++)
					{
						if (k == characterCreationHighlight)
							wattron(inboxMenu, A_REVERSE);
						mvwprintw(inboxMenu, k + 7, 2, characterCreationChoices[k].c_str());
						wattroff(inboxMenu, A_REVERSE);
					}
					characterCreationChoice = wgetch(inboxMenu);
					switch (characterCreationChoice)
					{
					case 'w':
					case KEY_UP:
						characterCreationHighlight--;
						if (characterCreationHighlight == -1)
							characterCreationHighlight = 1;
						break;
					case 's':
					case KEY_DOWN:
						characterCreationHighlight++;
						if (characterCreationHighlight == 2)
							characterCreationHighlight = 0;
						break;
					default:
						break;
					}
					if (characterCreationChoice == 10)
						break;
				}
				string inputCharacterCreation = characterCreationChoices[characterCreationHighlight];
				wrefresh(inboxMenu);
				if (inputCharacterCreation == "ENTER YOUR NAME")
				{
					echo();
					curs_set(1);
					wrefresh(inboxMenu);
					mvwscanw(inboxMenu, 14, 2, "%s", mainPlayer.name.c_str());
					wrefresh(inboxMenu);
					noecho();
					curs_set(0);
					mvwprintw(inboxMenu, 14, 2, "WELCOME, %s. Press any key to continue...", mainPlayer.name.c_str());
					mainPlayer.cash = 0;
					mainPlayer.strikes = 0;
					string playerSessionStrikes = " ";									//important value

					wrefresh(inboxMenu);
					getch();
					bool secondScreenLoop = false;
					while (!secondScreenLoop)
					{
						wrefresh(inboxMenu);
						WINDOW * secondScreenWin = newwin(20, 70, 1, 1);
						refresh();
						wborder(secondScreenWin, 0, 0, 0, 0, 0, 0, 0, 0);
						wattron(secondScreenWin, COLOR_PAIR(1));
						int secondScreenMaxY, secondScreenMaxX;
						getmaxyx(secondScreenWin, secondScreenMaxY, secondScreenMaxX);
						printMiddle(secondScreenWin, secondScreenMaxY, secondScreenMaxX, 9, "STUX NET");
						wattroff(secondScreenWin, COLOR_PAIR(1));

						wattron(secondScreenWin, COLOR_PAIR(4));
						mvwprintw(secondScreenWin, 1, 2, "NAME: %s", mainPlayer.name.c_str());
						wattroff(secondScreenWin, COLOR_PAIR(4));
						wattron(secondScreenWin, COLOR_PAIR(5));
						mvwprintw(secondScreenWin, 1, 55, "CASH: %d", mainPlayer.cash);
						wattroff(secondScreenWin, COLOR_PAIR(5));
						wattron(secondScreenWin, COLOR_PAIR(69));
						mvwprintw(secondScreenWin, 3, 31, "STRIKES: %s", playerSessionStrikes.c_str());
						wattroff(secondScreenWin, COLOR_PAIR(69));

						wattron(secondScreenWin, COLOR_PAIR(2));
						keypad(secondScreenWin, true);
						string secondScreenChoices[5] = { "INBOX", "BANK", "INVENTORY", "LEADERBOARDS", "GO BACK TO MAIN MENU" };
						int secondScreenChoice;
						int secondScreenHighlight = 0;
						while (1)
						{
							for (int l = 0; l < 5; l++)
							{
								if (l == secondScreenHighlight)
									wattron(secondScreenWin, A_REVERSE);
								mvwprintw(secondScreenWin, l + 7, 2, secondScreenChoices[l].c_str());
								wattroff(secondScreenWin, A_REVERSE);
							}
							secondScreenChoice = wgetch(secondScreenWin);
							switch (secondScreenChoice)
							{
							case 'w':
							case KEY_UP:
								secondScreenHighlight--;
								if (secondScreenHighlight == -1)
									secondScreenHighlight = 4;
								break;
							case 's':
							case KEY_DOWN:
								secondScreenHighlight++;
								if (secondScreenHighlight == 5)
									secondScreenHighlight = 0;
								break;
							default:
								break;
							}
							if (secondScreenChoice == 10)
								break;
						}
						string inputSecondScreen = secondScreenChoices[secondScreenHighlight];
						wrefresh(secondScreenWin);
						if (inputSecondScreen == "INBOX")
						{
							bool inboxLoop = false;
							while (!inboxLoop)
							{
								int email1Money, email2Money, email3Money;
								email1Money = 100;
								email2Money = email1Money * 2;
								email3Money = email2Money * 2;
								vector<string> possibleSender = { "Daniel", "Nick", "Hazar", "Rokkas", "Patryk", "Laur", "Dr Billings", "Dr Grawemeyer",
									"Hannah", "Bob", "Jim", "Simeon", "Marianne", "Fritzli", "Phyllis", "Ursulla",
									"Mike", "René", "Tyquoterius", "Andris", "Chez", "Svaraaj", "Saeed", "Yasser" };
								vector<string> possibleSubject = { "hacking his/her partners Facebook account", "breaking into the pentagon", "making his/her grades at school higher",
									"leaking the contents of a database", "'changing' the balance of his/her bank account", "performing an SQL Injection on a vulnernable website",
									"a DDoS attack on his/her school network" };
								int randomSender1, randomSender2, randomSender3;
								int randomSubject1, randomSubject2, randomSubject3;
								randomSender1 = rand() % possibleSender.size();
								randomSender2 = rand() % possibleSender.size();
								randomSender3 = rand() % possibleSender.size();
								randomSubject1 = rand() % possibleSubject.size();
								randomSubject2 = rand() % possibleSubject.size();
								randomSubject3 = rand() % possibleSubject.size();


								wrefresh(secondScreenWin);
								WINDOW * inboxMenu = newwin(20, 70, 1, 1);
								refresh();
								wborder(inboxMenu, 0, 0, 0, 0, 0, 0, 0, 0);
								wattron(inboxMenu, COLOR_PAIR(1));
								int inboxMaxY, inboxMaxX;
								getmaxyx(inboxMenu, inboxMaxY, inboxMaxX);
								printMiddle(inboxMenu, inboxMaxY, inboxMaxX, 9, "INBOX");
								wattroff(inboxMenu, COLOR_PAIR(1));

								keypad(inboxMenu, true);
								string inboxChoices[4] = { "EMAIL 1", "EMAIL 2", "EMAIL 3", "GO BACK" };
								int inboxChoice;
								int inboxHighlight = 0;
								while (1)
								{
									for (int m = 0; m < 4; m++)
									{
										wattron(inboxMenu, COLOR_PAIR(69));
										if (m == inboxHighlight)
											wattron(inboxMenu, A_REVERSE);

										mvwprintw(inboxMenu, 5 * m + 3, 3, inboxChoices[m].c_str());

										wattroff(inboxMenu, A_REVERSE);
										wattroff(inboxMenu, COLOR_PAIR(69));

										for (int n = 0; n < 3; n++)
										{
											if (m == 0)
											{
												if (possibleSender[randomSender1] == possibleSender[0] || possibleSender[randomSender1] == possibleSender[1] || possibleSender[randomSender1] == possibleSender[2] || possibleSender[randomSender1] == possibleSender[3] || possibleSender[randomSender1] == possibleSender[4] || possibleSender[randomSender1] == possibleSender[5])
												{
													wattron(inboxMenu, COLOR_PAIR(69));
													mvwprintw(inboxMenu, (5 * m + 3) + 1, 3, "Sender: %s", possibleSender[randomSender1].c_str());
													mvwprintw(inboxMenu, (5 * m + 3) + 2, 3, "Subject: %s", possibleSubject[randomSubject1].c_str());
													wattroff(inboxMenu, COLOR_PAIR(69));
													wattron(inboxMenu, COLOR_PAIR(5));
													mvwprintw(inboxMenu, (5 * m + 3) + 3, 3, "Reward: %d", email1Money);
													wattroff(inboxMenu, COLOR_PAIR(5));
												}
												else
												{
													wattron(inboxMenu, COLOR_PAIR(2));
													mvwprintw(inboxMenu, (5 * m + 3) + 1, 3, "Sender: %s", possibleSender[randomSender1].c_str());
													mvwprintw(inboxMenu, (5 * m + 3) + 2, 3, "Subject: %s", possibleSubject[randomSubject1].c_str());
													wattroff(inboxMenu, COLOR_PAIR(2));
													wattron(inboxMenu, COLOR_PAIR(5));
													mvwprintw(inboxMenu, (5 * m + 3) + 3, 3, "Reward: %d", email1Money);
													wattroff(inboxMenu, COLOR_PAIR(5));
												}
											}
											if (m == 1)
											{
												if (possibleSender[randomSender2] == possibleSender[6] || possibleSender[randomSender2] == possibleSender[7])
												{
													wattron(inboxMenu, COLOR_PAIR(3));
													mvwprintw(inboxMenu, (5 * m + 3) + 1, 3, "Sender: %s", possibleSender[randomSender2].c_str());
													mvwprintw(inboxMenu, (5 * m + 3) + 2, 3, "Subject: %s", possibleSubject[randomSubject2].c_str());
													wattroff(inboxMenu, COLOR_PAIR(3));
													wattron(inboxMenu, COLOR_PAIR(5));
													mvwprintw(inboxMenu, (5 * m + 3) + 3, 3, "Reward: %d", email2Money);
													wattroff(inboxMenu, COLOR_PAIR(5));
												}
												else
												{
													wattron(inboxMenu, COLOR_PAIR(2));
													mvwprintw(inboxMenu, (5 * m + 3) + 1, 3, "Sender: %s", possibleSender[randomSender2].c_str());
													mvwprintw(inboxMenu, (5 * m + 3) + 2, 3, "Subject: %s", possibleSubject[randomSubject2].c_str());
													wattroff(inboxMenu, COLOR_PAIR(2));
													wattron(inboxMenu, COLOR_PAIR(5));
													mvwprintw(inboxMenu, (5 * m + 3) + 3, 3, "Reward: %d", email2Money);
													wattroff(inboxMenu, COLOR_PAIR(5));
												}
											}
											if (m == 2)
											{
												wattron(inboxMenu, COLOR_PAIR(2));
												mvwprintw(inboxMenu, (5 * m + 3) + 1, 3, "Sender: %s", possibleSender[randomSender3].c_str());
												mvwprintw(inboxMenu, (5 * m + 3) + 2, 3, "Subject: %s", possibleSubject[randomSubject3].c_str());
												wattroff(inboxMenu, COLOR_PAIR(2));
												wattron(inboxMenu, COLOR_PAIR(5));
												mvwprintw(inboxMenu, (5 * m + 3) + 3, 3, "Reward: %d", email3Money);
												wattroff(inboxMenu, COLOR_PAIR(5));
											}

										}

									}

									inboxChoice = wgetch(inboxMenu);
									switch (inboxChoice)
									{
									case 'w':
									case KEY_UP:
										inboxHighlight--;
										if (inboxHighlight == -1)
											inboxHighlight = 3;
										break;
									case 's':
									case KEY_DOWN:
										inboxHighlight++;
										if (inboxHighlight == 4)
											inboxHighlight = 0;
										break;
									default:
										break;
									}
									if (inboxChoice == 10)
										break;
								}
								string inboxMenuInput = inboxChoices[inboxHighlight];
								wrefresh(inboxMenu);
								if (inboxMenuInput == "EMAIL 1")
								{
									bool danielGameLoop = false;
									while (!danielGameLoop)
									{
										wrefresh(inboxMenu);
										int danielGameMaxY, danielGameMaxX;
										WINDOW * danielGameWin = newwin(20, 75, 1, 1);
										getmaxyx(danielGameWin, danielGameMaxY, danielGameMaxX);
										refresh();
										keypad(danielGameWin, true);
										//wborder(danielGameWin, 0, 0, 0, 0, 0, 0, 0, 0);
										wattron(danielGameWin, COLOR_PAIR(1));
										mvwprintw(danielGameWin, 7, 1, "You are about to embark on a mission to help %s involving", possibleSender[randomSender1].c_str());
										mvwprintw(danielGameWin, 8, 1, "helping him/her with %s.", possibleSubject[randomSubject1].c_str());
										wrefresh(danielGameWin);
										getch();
										wclear(danielGameWin);
										mvwprintw(danielGameWin, 7, 1, "For this mission, you are going to have to enter the field.");
										mvwprintw(danielGameWin, 9, 1, "Control the player by using");
										wattroff(danielGameWin, COLOR_PAIR(1));
										wattron(danielGameWin, COLOR_PAIR(69));
										mvwprintw(danielGameWin, 9, 29, "W, A, S, D.");
										wattroff(danielGameWin, COLOR_PAIR(69));
										wattron(danielGameWin, COLOR_PAIR(1));
										mvwprintw(danielGameWin, 11, 1, "The player will be marked with an");
										wattroff(danielGameWin, COLOR_PAIR(1));
										wattron(danielGameWin, COLOR_PAIR(5));
										mvwprintw(danielGameWin, 11, 35, "'@'.");
										wattroff(danielGameWin, COLOR_PAIR(5));
										wattron(danielGameWin, COLOR_PAIR(1));
										mvwprintw(danielGameWin, 13, 1, "To exit the game at any time, press");
										wattroff(danielGameWin, COLOR_PAIR(1));
										wattron(danielGameWin, COLOR_PAIR(69));
										mvwprintw(danielGameWin, 13, 37, "'x'.");
										wattroff(danielGameWin, COLOR_PAIR(69));
										wrefresh(danielGameWin);
										getch();
										wclear(danielGameWin);
										//daniel game stuff


										char ** level;
										int danielGameInput;
										Position * newPosition;

										mapSetup(danielGameWin);

										level = saveLevelPositions(danielGameWin);

										DanielGamePlayer = playerSetup(danielGameWin);				//main game initiations
										int mainEloRating = DanielGamePlayer->eloRating;
										mainEloRating = 1400;
										keypad(danielGameWin, true);
										mvwprintw(danielGameWin, 1, 1, "Elo rating: %d", mainEloRating);

										wrefresh(danielGameWin);									//note: DanielGamePlayer is object of class DanielPlayer
										while ((danielGameInput = getch()) != 'x')
										{

											newPosition = handlePlayerInput(danielGameWin, danielGameInput, DanielGamePlayer);
											checkPosition(danielGameWin, newPosition, DanielGamePlayer, level);
											wrefresh(danielGameWin);
										}

										endwin();
										danielGameLoop = true;
										refresh();
									}
								}

								if (inboxMenuInput == "GO BACK")
								{

									inboxLoop = true;
									refresh();
								}


							}
						}
						if (inputSecondScreen == "GO BACK TO MAIN MENU")
						{
							characterCreationLoop = true;
							secondScreenLoop = true;
							refresh();
						}

						wrefresh(secondScreenWin);
					}


				}
				if (inputCharacterCreation == "GO BACK")
				{
					characterCreationLoop = true;
					refresh();
				}
				wrefresh(inboxMenu);
			}
		}
		if (inputMainMenu == "EXIT")
		{
			mainMenuLoop = true;
			endwin();
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
				int instructionMaxY, instructionMaxX;
				getmaxyx(howToPlay, instructionMaxY, instructionMaxX);
				wattron(howToPlay, COLOR_PAIR(1));
				printMiddle(howToPlay, instructionMaxY, instructionMaxX, 9, stux1);
				printMiddle(howToPlay, instructionMaxY, instructionMaxX, 8, stux2);
				printMiddle(howToPlay, instructionMaxY, instructionMaxX, 7, stux3);
				printMiddle(howToPlay, instructionMaxY, instructionMaxX, 6, stux4);
				printMiddle(howToPlay, instructionMaxY, instructionMaxX, 5, stux5);
				wattroff(howToPlay, COLOR_PAIR(1));
				wattron(howToPlay, COLOR_PAIR(69));
				printMiddle(howToPlay, instructionMaxY, instructionMaxX, 4, "INSTRUCTIONS");
				wattroff(howToPlay, COLOR_PAIR(69));
				string instructionString = "WELCOME TO STUXNET                                    ";
				string instructionString1 = "TO BEGIN THE GAME, SELECT THE 'PLAY' OPTION AND       ";
				string instructionString2 = "ENTER YOUR DESIRED ALIAS.                             ";												//work on
				string instructionString3 = "THE GAME WILL PRESENT YOU WITH A SERIES OF CHALLENGES ";
				string instructionString4 = "IN THE FORM OF EMAILS FROM PAYING CUSTOMERS.          ";
				string instructionString5 = "COMPLETE THEM AND YOU WILL PROGRESS ON YOUR PATH TO - ";
				string instructionString6 = "BECOMING A FORMIDDABLE HACKER.                        ";
				wattron(howToPlay, COLOR_PAIR(6));
				mvwprintw(howToPlay, 7, 7, instructionString.c_str());
				mvwprintw(howToPlay, 8, 7, instructionString1.c_str());
				mvwprintw(howToPlay, 9, 7, instructionString2.c_str());
				mvwprintw(howToPlay, 10, 7, instructionString3.c_str());
				mvwprintw(howToPlay, 11, 7, instructionString4.c_str());
				mvwprintw(howToPlay, 12, 7, instructionString5.c_str());
				mvwprintw(howToPlay, 13, 7, instructionString6.c_str());

				wattroff(howToPlay, COLOR_PAIR(6));


				/*int x = test.length();
				mvwprintw(howToPlay, howToMaxY/2, (howToMaxX-x)/2, test.c_str());*/   // <- alternative way if my function fails



				wattroff(howToPlay, COLOR_PAIR(1));
				wattron(howToPlay, COLOR_PAIR(2));
				keypad(howToPlay, true);
				string howToPlayChoices[1] = { "GO BACK" };
				int howToPlayChoice;
				int howToPlayHighlight = 0;
				while (1)
				{
					for (int m = 0; m < 1; m++)
					{
						if (m == howToPlayHighlight)
							wattron(howToPlay, A_REVERSE);
						mvwprintw(howToPlay, m + 17, 2, howToPlayChoices[m].c_str());
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
