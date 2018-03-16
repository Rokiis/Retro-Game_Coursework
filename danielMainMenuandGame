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
#include <math.h>
#include <sqlite3.h>


using namespace std;
bool mainMenuLoop = false;

int winMatch(float computerHackChance, float playerHackBonus)
{
	int x = (rand() % 100);
	float hackChance = computerHackChance + playerHackBonus;
	if (x <= hackChance)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
float eloExpected(float rating1, float rating2)
{
	float calc = (1.0 / (1.0 + pow(10, ((rating2 - rating1) / 400))));
	return calc;
}
float elo(float old, float exp, float score, float k)
{
	float mainScore = old + k * (score - exp);
	return mainScore;
}
void eloToRank(WINDOW * win, int elo)
{
	if (elo <= 1320)
	{
		wrefresh(win);
		wattron(win, COLOR_PAIR(10));
		mvwprintw(win, 0, 1, "RANK: BRONZE");
		wattroff(win, COLOR_PAIR(10));
		wrefresh(win);

	}
	else if (elo <= 1390)
	{
		wrefresh(win);
		wattron(win, COLOR_PAIR(7));
		mvwprintw(win, 0, 1, "RANK: SILVER");
		wattroff(win, COLOR_PAIR(7));
		wrefresh(win);
	}
	else if (elo == 1400)
	{
		wrefresh(win);
		wattron(win, COLOR_PAIR(4));
		mvwprintw(win, 0, 1, "RANK: UNRANKED");
		wattroff(win, COLOR_PAIR(4));
		wrefresh(win);
	}
	else if (elo >= 1420 && elo <=1450)
	{
		wrefresh(win);
		wattron(win, COLOR_PAIR(5));
		mvwprintw(win, 0, 1, "RANK: GOLD");
		wattroff(win, COLOR_PAIR(5));
		wrefresh(win);
	}
	else if (elo >= 1451 && elo <= 1500)
	{
		wrefresh(win);
		wattron(win, COLOR_PAIR(2));
		mvwprintw(win, 0, 1, "RANK: PLATINUM");
		wattroff(win, COLOR_PAIR(2));
		wrefresh(win);
	}
	else if (elo > 1500)
	{
		wrefresh(win);
		wattron(win, COLOR_PAIR(3));
		mvwprintw(win, 0, 1, "RANK: MASTER");
		wattroff(win, COLOR_PAIR(3));
		wrefresh(win);
	}
	else
	{
		wrefresh(win);
		mvwprintw(win, 0, 1, "RANK: UNRANKED");
		wrefresh(win);
	}
}

typedef struct Level
{
	char ** tiles;
	int level;
	int numberOfRooms;
	struct Room ** rooms;
} Level;

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
void printMiddle(WINDOW * win, int y, int x, int upDown, string asd) //function I created to print text within a window at the centre.
{
	int getLength = asd.length();									 //int upDown is buggy. 9 = top of screen, play around with it. 
	int newY = (y / 2) - upDown;
	int newX = (x - getLength) / 2;
	mvwprintw(win, newY, newX, asd.c_str());
}



//map
Room ** roomSetup(WINDOW * window);
char ** saveLevelPositions(WINDOW * win);
//player
DanielPlayer * playerSetup(WINDOW * win);
Position * handlePlayerInput(WINDOW * win, int input, DanielPlayer * DanielGamePlayer);
int checkPosition(WINDOW * win, Position * newPosition, DanielPlayer * DanielGamePlayer, char ** level);
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
Level * createLevel(WINDOW * win, int level)
{
	Level * newLevel;
	newLevel = (Level *)malloc(sizeof(Level));

	newLevel->level = level;
	newLevel->numberOfRooms = 3;
	newLevel->rooms = roomSetup(win);
	newLevel->tiles = saveLevelPositions(win);
	return newLevel;

}

Room ** roomSetup(WINDOW * window)
{
	Room ** rooms;
	rooms = (Room **)malloc(sizeof(Room) * 6);

	vector<int> heightPicker = { 4, 5, 6, 7, 8 };
	vector<int> widthPicker = { 7, 8, 9, 10, 11, 12 };


	/*
	int rPicker1 = rand() % heightPicker.size();
	int rPicker2 = rand() % widthPicker.size();
	int rPicker3 = rand() % heightPicker.size();
	int rPicker4 = rand() % widthPicker.size();
	//work on
	int rHeight1 = heightPicker[rPicker1];
	int rWidth1 = widthPicker[rPicker2];
	int rHeight2 = heightPicker[rPicker3];
	int rWidth2 = widthPicker[rPicker4];
	*/

	rooms[0] = createRoom(10, 40, 7, 11);
	drawRoom(window, rooms[0]);

	rooms[1] = createRoom(9, 5, 6, 11); //up/down, left/right, height, width
	drawRoom(window, rooms[1]);

	rooms[2] = createRoom(1, 50, 3, 10);
	drawRoom(window, rooms[2]);

	doorPath(window, rooms[1]->doors[3], rooms[0]->doors[1]);			//0=top,1=left,2=bottom,3=right
	doorPath(window, rooms[2]->doors[2], rooms[0]->doors[0]);
	doorPath(window, rooms[2]->doors[1], rooms[1]->doors[0]);


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
		mvwprintw(win, room->position.y, x, "="); //top
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

	//draw computers
	
	


	mvwprintw(win, 11, 7, "C"); //work on
	mvwprintw(win, 15, 45, "C");
	mvwprintw(win, 2, 53, "C");


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
int checkPosition(WINDOW * win, Position * newPosition, DanielPlayer * DanielGamePlayer, char ** level)
{
	int space;
	switch (mvwinch(win, newPosition->y, newPosition->x))		//checks character collision
	{
	case '.':
	case '#':
	case '+':
		playerMove(win, newPosition, DanielGamePlayer, level);
		break;
	case 'C':
		playerMove(win, newPosition, DanielGamePlayer, level);
		return 69;
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

	newPlayer->position.y = 12;			//starting positions
	newPlayer->position.x = 10;    //increase = further right, decrease further left
	newPlayer->health = 10;
	wattron(win, COLOR_PAIR(5));
	mvwprintw(win, newPlayer->position.y, newPlayer->position.x, "@");
	move(newPlayer->position.y, newPlayer->position.x);
	wattroff(win, COLOR_PAIR(5));
	return newPlayer;
}
//functions below are for the main menu. above are for daniel's game. 


class MainGamePlayer
{
public:
	string name;
	int strikes;			//used for main menu stats only
	int cash;
	int amountHacked;
};




int main()
{
	srand(time(NULL)); //implement seed function
	sqlite3 *db;
	sqlite3_stmt * stmt;
	int database;
	database = sqlite3_open("danielDatabase.db", &db);
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

		init_pair(1, 10, 0);		//light green
		init_pair(69, 12, 0);	//colour initialisations	light red
		init_pair(2, COLOR_CYAN, 0);
		init_pair(3, COLOR_MAGENTA, 0);
		init_pair(4, COLOR_WHITE, 0);
		init_pair(5, 14, 0);
		init_pair(6, COLOR_WHITE, 4);
		init_pair(7, 8, 0);		//grey 
		init_pair(10, 4, 0);


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
					int mainEloRating = 1400;
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
					mainPlayer.amountHacked = 0;
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
						string secondScreenChoices[5] = { "INBOX", "BANK", "INVENTORY", "LEADERBOARD", "GO BACK TO MAIN MENU" };
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
								vector<string> possibleSender = { "Daniel", "Hugh", "Nick", "Hazar", "Rokkas", "Patryk", "Laur", "Dr Billings", "Dr Grawemeyer",
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
								curs_set(0);
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
													mvwprintw(inboxMenu, (5 * m + 3) + 3, 3, "Reward Potential: %d", email1Money);
													wattroff(inboxMenu, COLOR_PAIR(5));
												}
												else
												{
													wattron(inboxMenu, COLOR_PAIR(2));
													mvwprintw(inboxMenu, (5 * m + 3) + 1, 3, "Sender: %s", possibleSender[randomSender1].c_str());
													mvwprintw(inboxMenu, (5 * m + 3) + 2, 3, "Subject: %s", possibleSubject[randomSubject1].c_str());
													wattroff(inboxMenu, COLOR_PAIR(2));
													wattron(inboxMenu, COLOR_PAIR(5));
													mvwprintw(inboxMenu, (5 * m + 3) + 3, 3, "Reward Potential: %d", email1Money);
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
													mvwprintw(inboxMenu, (5 * m + 3) + 3, 3, "Reward Potential: %d", email2Money);
													wattroff(inboxMenu, COLOR_PAIR(5));
												}
												else
												{
													wattron(inboxMenu, COLOR_PAIR(2));
													mvwprintw(inboxMenu, (5 * m + 3) + 1, 3, "Sender: %s", possibleSender[randomSender2].c_str());
													mvwprintw(inboxMenu, (5 * m + 3) + 2, 3, "Subject: %s", possibleSubject[randomSubject2].c_str());
													wattroff(inboxMenu, COLOR_PAIR(2));
													wattron(inboxMenu, COLOR_PAIR(5));
													mvwprintw(inboxMenu, (5 * m + 3) + 3, 3, "Reward Potential: %d", email2Money);
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
												mvwprintw(inboxMenu, (5 * m + 3) + 3, 3, "Reward Potential: %d", email3Money);
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
										bool preLoop = false;
										while (!preLoop)
										{
											bool danielMainGameLoop = false;
											while (!danielMainGameLoop)
											{
												wclear(danielGameWin);
												//daniel game stuff



												int danielGameInput;

												Position * newPosition;

												Level * level;

												level = createLevel(danielGameWin, 0);


												DanielGamePlayer = playerSetup(danielGameWin);				//main game initiations


												keypad(danielGameWin, true);
												eloToRank(danielGameWin, mainEloRating);		//handles player ranking system
												mvwprintw(danielGameWin, 0, 20, "Name: %s", mainPlayer.name.c_str());
												mvwprintw(danielGameWin, 0, 40, "Amount hacked: %d", mainPlayer.amountHacked);
												
												wrefresh(danielGameWin);									//note: DanielGamePlayer is object of class DanielPlayer
												while (danielGameInput = getch())
												{
													newPosition = handlePlayerInput(danielGameWin, danielGameInput, DanielGamePlayer);
													int x = checkPosition(danielGameWin, newPosition, DanielGamePlayer, level->tiles);
													wrefresh(danielGameWin);
													if (x == 69)
													{
														bool battleLoop = false;
														while (!battleLoop)
															break;
														{
															vector<string> possibleComputers = { "CRAY TITAN", "IBM SEQUOIA", "FUJITSU K COMPUTER", "TIANHE-1", "TIANHE-2", "SUNWAY TAIHULIGHT", "TRINITY", "MIRA", "PIZ DAINT", "CRAY-1", "CDC 6600", "ATLAS", "IBM STRETCH (7030)" };
															int possibleComputerPick = rand() % possibleComputers.size();
															string superComputer = possibleComputers[possibleComputerPick];
															vector<int> possibleElo = { 100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900 };
															int initialKFactor = 20;
															int possibleEloPick = rand() % possibleElo.size();
															int computerElo = possibleElo[possibleEloPick];
															float eloExpectedP;
															float eloExpectedC;
															
															string clear1 = "                                                        ";
															string clear2 = "                                                        ";
															string clear3 = "                                                        ";
															string clear4 = "                                                        ";
															string clear5 = "                                                        ";


															string titan1 = "TTTTTT III TTTTTT  AA  N   N";
															string titan2 = "  TT    I    TT   A  A NN  N";
															string titan3 = "  TT    I    TT   AAAA N N N";
															string titan4 = "  TT    I    TT   A  A N  NN";
															string titan5 = "  TT   III   TT   A  A N   N";

															string ibm1 = "III BBBB  M   M";
															string ibm2 = " I  B   B MM MM";
															string ibm3 = " I  BBBB  M M M";
															string ibm4 = " I  B   B M   M";
															string ibm5 = "III BBBB  M   M";

															string fujitsu1 = "FFFF U   U     J III TTTTTT  SSS  U   U";
															string fujitsu2 = "F    U   U     J  I    TT   S     U   U";
															string fujitsu3 = "FFF  U   U     J  I    TT    SSS  U   U";
															string fujitsu4 = "F    U   U J   J  I    TT       S U   U";
															string fujitsu5 = "F     UUU   JJJ  III   TT   SSSS   UUU ";

															string tianhe1 = "TTTTTT III  AA  N   N H  H EEEE";
															string tianhe2 = "  TT    I  A  A NN  N H  H E   ";
															string tianhe3 = "  TT    I  AAAA N N N HHHH EEE ";
															string tianhe4 = "  TT    I  A  A N  NN H  H E   ";
															string tianhe5 = "  TT   III A  A N   N H  H EEEE";

															string trinity1 = "TTTTTT RRRR  III N   N III TTTTTT Y   Y";
															string trinity2 = "  TT   R   R  I  NN  N  I    TT    Y Y ";
															string trinity3 = "  TT   RRRR   I  N N N  I    TT     Y  ";
															string trinity4 = "  TT   R R    I  N  NN  I    TT     Y  ";
															string trinity5 = "  TT   R  RR III N   N III   TT     Y  ";
															
															string hannah1 = "c(°  )";
															string hannah2 = "/(   )/";
															string hannah3 = " -   -";

															string hannah4 = "<(o  )";
															string hannah5 = " ( ''>  )>";

															eloExpectedP = eloExpected(mainEloRating, computerElo * 5);			//get expected elo rating
															eloExpectedC = eloExpected(computerElo * 5, mainEloRating);

															float computerHackChance = computerElo / 10;
															float playerHackBonus = mainEloRating / 100;

															WINDOW * battleWindow = newwin(20, 75, 1, 1);
															int battleMaxY, battleMaxX;
															getmaxyx(battleWindow, battleMaxY, battleMaxX);
															refresh();
															wattron(battleWindow, COLOR_PAIR(1));
															mvwprintw(battleWindow, 10, 15, "YOU HAVE ENCOUNTERED THE %s SUPER COMPUTER -", superComputer.c_str());
															mvwprintw(battleWindow, 11, 15, "WITH POWER LEVEL %d", computerElo);
															mvwprintw(battleWindow, 13, 15, "TO GET ON WITH YOUR MISSION, PRESS ANY KEY TO CONTINUE...");
															wrefresh(battleWindow);
															wattroff(battleWindow, COLOR_PAIR(1));
															getch();
															mvwprintw(battleWindow, 10, 15, "                                                                        ");
															mvwprintw(battleWindow, 11, 15, "                                                                        ");	//clean output
															mvwprintw(battleWindow, 13, 15, "                                                                        ");
															wrefresh(battleWindow);

															wborder(battleWindow, 0, 0, 0, 0, 0, 0, 0, 0);
															
															wattron(battleWindow, COLOR_PAIR(69));
															printMiddle(battleWindow, battleMaxY, battleMaxX, 9, "BREACH THE SUPERCOMPUTER");
															vector<int>colourList = { 1, 2, 3, 4, 5, 6, 7, 10, 69 };
															int colourPicker = rand() % colourList.size();
															if (possibleComputers[possibleComputerPick] == possibleComputers[1] || possibleComputers[possibleComputerPick] == possibleComputers[12])
															{
																wattron(battleWindow, COLOR_PAIR(colourList[colourPicker]));
																printMiddle(battleWindow, battleMaxY, battleMaxX, 6, ibm1);
																printMiddle(battleWindow, battleMaxY, battleMaxX, 5, ibm2);
																printMiddle(battleWindow, battleMaxY, battleMaxX, 4, ibm3);
																printMiddle(battleWindow, battleMaxY, battleMaxX, 3, ibm4);
																printMiddle(battleWindow, battleMaxY, battleMaxX, 2, ibm5);
																wattroff(battleWindow, COLOR_PAIR(colourList[colourPicker]));


															}
															else if (possibleComputers[possibleComputerPick] == possibleComputers[0])
															{
																wattron(battleWindow, COLOR_PAIR(colourList[colourPicker]));
																printMiddle(battleWindow, battleMaxY, battleMaxX, 6, titan1);
																printMiddle(battleWindow, battleMaxY, battleMaxX, 5, titan2);
																printMiddle(battleWindow, battleMaxY, battleMaxX, 4, titan3);
																printMiddle(battleWindow, battleMaxY, battleMaxX, 3, titan4);
																printMiddle(battleWindow, battleMaxY, battleMaxX, 2, titan5);
																wattroff(battleWindow, COLOR_PAIR(colourList[colourPicker]));
															}
															else if (possibleComputers[possibleComputerPick] == possibleComputers[2])
															{
																wattron(battleWindow, COLOR_PAIR(colourList[colourPicker]));
																printMiddle(battleWindow, battleMaxY, battleMaxX, 6, fujitsu1);
																printMiddle(battleWindow, battleMaxY, battleMaxX, 5, fujitsu2);
																printMiddle(battleWindow, battleMaxY, battleMaxX, 4, fujitsu3);
																printMiddle(battleWindow, battleMaxY, battleMaxX, 3, fujitsu4);
																printMiddle(battleWindow, battleMaxY, battleMaxX, 2, fujitsu5);
																wattroff(battleWindow, COLOR_PAIR(colourList[colourPicker]));
															}
															else if (possibleComputers[possibleComputerPick] == possibleComputers[3] || possibleComputers[possibleComputerPick] == possibleComputers[4])
															{
																wattron(battleWindow, COLOR_PAIR(colourList[colourPicker]));
																printMiddle(battleWindow, battleMaxY, battleMaxX, 6, tianhe1);
																printMiddle(battleWindow, battleMaxY, battleMaxX, 5, tianhe2);
																printMiddle(battleWindow, battleMaxY, battleMaxX, 4, tianhe3);
																printMiddle(battleWindow, battleMaxY, battleMaxX, 3, tianhe4);
																printMiddle(battleWindow, battleMaxY, battleMaxX, 2, tianhe5);
																wattroff(battleWindow, COLOR_PAIR(colourList[colourPicker]));
															}
															else if (possibleComputers[possibleComputerPick] == possibleComputers[6])
															{
																wattron(battleWindow, COLOR_PAIR(colourList[colourPicker]));
																printMiddle(battleWindow, battleMaxY, battleMaxX, 6, trinity1);
																printMiddle(battleWindow, battleMaxY, battleMaxX, 5, trinity2);
																printMiddle(battleWindow, battleMaxY, battleMaxX, 4, trinity3);
																printMiddle(battleWindow, battleMaxY, battleMaxX, 3, trinity4);
																printMiddle(battleWindow, battleMaxY, battleMaxX, 2, trinity5);
																wattroff(battleWindow, COLOR_PAIR(colourList[colourPicker]));
															}
															else if (possibleComputers[possibleComputerPick] == possibleComputers[7])
															{
																wattron(battleWindow, COLOR_PAIR(colourList[colourPicker]));
																printMiddle(battleWindow, battleMaxY, battleMaxX, 6, hannah1);
																printMiddle(battleWindow, battleMaxY, battleMaxX, 5, hannah2);
																printMiddle(battleWindow, battleMaxY, battleMaxX, 4, hannah3);
																wattroff(battleWindow, COLOR_PAIR(colourList[colourPicker]));
															}
															else if (possibleComputers[possibleComputerPick] == possibleComputers[5])
															{
																wattron(battleWindow, COLOR_PAIR(colourList[colourPicker]));
																printMiddle(battleWindow, battleMaxY, battleMaxX, 6, hannah4);
																printMiddle(battleWindow, battleMaxY, battleMaxX, 5, hannah5);
																wattroff(battleWindow, COLOR_PAIR(colourList[colourPicker]));
															}
															wrefresh(battleWindow);
															wattroff(battleWindow, COLOR_PAIR(69));
															keypad(battleWindow, true);
															wattron(battleWindow, COLOR_PAIR(1));
															string battleChoices[4] = { "HACK", "USE TOOL", "FOCUS", "FLEE" };
															int battleChoice;
															int battleHighlight = 0;
															while (1)
															{
																for (int i = 0; i < 5; i++)
																{
																	if (i == battleHighlight)
																		wattron(battleWindow, A_REVERSE);
																	if (i == 0)
																	{
																		mvwprintw(battleWindow, i + 12, 3, battleChoices[i].c_str());
																	}
																	if (i == 1)
																	{
																		mvwprintw(battleWindow, i + 11, 30, battleChoices[i].c_str());
																	}
																	if (i == 2)
																	{
																		mvwprintw(battleWindow, i + 13, 3, battleChoices[i].c_str());
																	}
																	if (i == 3)
																	{
																		mvwprintw(battleWindow, i + 12, 30, battleChoices[i].c_str());
																	}
																	wattroff(battleWindow, A_REVERSE);
																}
																
																battleChoice = wgetch(battleWindow);
																switch (battleChoice)
																{
																case 'a':
																case KEY_LEFT:
																	battleHighlight--;
																	if (battleHighlight == -1)
																		battleHighlight = 0;
																	if (battleHighlight == 1)
																		battleHighlight = 2;
																	if (battleHighlight == 0)
																		battleHighlight = 0;
																	if (battleHighlight == 2)
																		battleHighlight = 2;
																	break;
																case 's':
																case KEY_DOWN:
																	battleHighlight--, battleHighlight--;
																	if (battleHighlight == -2)
																		battleHighlight = 2;
																	if (battleHighlight == -1)
																		battleHighlight = 3;
																	if (battleHighlight == 0)
																		battleHighlight = 2;
																	if (battleHighlight == 1)
																		battleHighlight = 3;
																	break;
																case 'd':
																case KEY_RIGHT:
																	battleHighlight++;							//calculations to get menu for game, logic is simple - if highlight is equal to number in array that it will be (after applying ++ or --), then go to x element of array.
																	if (battleHighlight == 1)
																		battleHighlight = 1;
																	if (battleHighlight == 2)
																		battleHighlight = 1;
																	if (battleHighlight == 2)
																		battleHighlight = 3;
																	if (battleHighlight == 4)
																		battleHighlight = 3;
																	break;
																case 'w':
																case KEY_UP:
																	battleHighlight++, battleHighlight++;
																	if (battleHighlight == 2)
																		battleHighlight = 0;
																	if (battleHighlight == 3)
																		battleHighlight = 1;
																	if (battleHighlight == 4)
																		battleHighlight = 0;
																	if (battleHighlight == 5)
																		battleHighlight = 1;
																	break;
																default:
																	break;
																}
																if (battleChoice == 10)
																	break;
															}
														
															string inputBattle = battleChoices[battleHighlight];
															wattroff(battleWindow, COLOR_PAIR(1));
															wrefresh(battleWindow);
															if (inputBattle == "HACK")
															{
																printMiddle(battleWindow, battleMaxY, battleMaxX, 6, clear1);
																printMiddle(battleWindow, battleMaxY, battleMaxX, 5, clear2);
																printMiddle(battleWindow, battleMaxY, battleMaxX, 4, clear3);
																printMiddle(battleWindow, battleMaxY, battleMaxX, 3, clear4);
																printMiddle(battleWindow, battleMaxY, battleMaxX, 2, clear5);
																wrefresh(battleWindow);
																printMiddle(battleWindow, battleMaxY, battleMaxX, 4, "You attempt to hack the computer...");
																wrefresh(battleWindow);
																getch();
																int winLoss = winMatch(computerHackChance, playerHackBonus);	//calculates percentage chance of winning, generates random number and returns 1 (for win) and 0 (for loss)
																mainEloRating = elo(mainEloRating, eloExpectedP, winLoss, initialKFactor); //update elo rating
																if (winLoss == 1)
																{
																	printMiddle(battleWindow, battleMaxY, battleMaxX, 6, clear1);
																	printMiddle(battleWindow, battleMaxY, battleMaxX, 5, clear2);
																	printMiddle(battleWindow, battleMaxY, battleMaxX, 4, clear3);
																	printMiddle(battleWindow, battleMaxY, battleMaxX, 3, clear4);
																	printMiddle(battleWindow, battleMaxY, battleMaxX, 2, clear5);
																	wrefresh(battleWindow);
																	printMiddle(battleWindow, battleMaxY, battleMaxX, 4, "You have succesfully hacked the computer!");
																	mainPlayer.cash += computerElo / 10;		//player cash gain	
																	mainPlayer.amountHacked += 1;
																}
																else
																{
																	printMiddle(battleWindow, battleMaxY, battleMaxX, 6, clear1);
																	printMiddle(battleWindow, battleMaxY, battleMaxX, 5, clear2);
																	printMiddle(battleWindow, battleMaxY, battleMaxX, 4, clear3);
																	printMiddle(battleWindow, battleMaxY, battleMaxX, 3, clear4);
																	printMiddle(battleWindow, battleMaxY, battleMaxX, 2, clear5);
																	wrefresh(battleWindow);
																	printMiddle(battleWindow, battleMaxY, battleMaxX, 4, "You have failed to hack the computer...");
																}
																wrefresh(battleWindow);
																getch();
																break;
															}
															else if (inputBattle == "FLEE")
															{
																printMiddle(battleWindow, battleMaxY, battleMaxX, 6, clear1);
																printMiddle(battleWindow, battleMaxY, battleMaxX, 5, clear2);
																printMiddle(battleWindow, battleMaxY, battleMaxX, 4, clear3);
																printMiddle(battleWindow, battleMaxY, battleMaxX, 3, clear4);
																printMiddle(battleWindow, battleMaxY, battleMaxX, 2, clear5);
																wrefresh(battleWindow);
																mainEloRating -= 10;
																printMiddle(battleWindow, battleMaxY, battleMaxX, 4, "You stop what you were doing with the computer and leave...");
																wrefresh(battleWindow);
																getch();
																break;

															}
															else if (inputBattle == "FOCUS")
															{
																printMiddle(battleWindow, battleMaxY, battleMaxX, 6, clear1);
																printMiddle(battleWindow, battleMaxY, battleMaxX, 5, clear2);
																printMiddle(battleWindow, battleMaxY, battleMaxX, 4, clear3);
																printMiddle(battleWindow, battleMaxY, battleMaxX, 3, clear4);
																printMiddle(battleWindow, battleMaxY, battleMaxX, 2, clear5);
																wrefresh(battleWindow);
																mainEloRating -= 10; 
																printMiddle(battleWindow, battleMaxY, battleMaxX, 4, "You break into a sweat in attempt to penetrate the computer...");
																wrefresh(battleWindow);
																printMiddle(battleWindow, battleMaxY, battleMaxX, 4, "                                                                   ");
																getch();
																int winLoss = winMatch(computerHackChance, playerHackBonus + 10);
																mainEloRating = elo(mainEloRating, eloExpectedP, winLoss, initialKFactor);
																if (winLoss == 1)
																{
																	printMiddle(battleWindow, battleMaxY, battleMaxX, 6, clear1);
																	printMiddle(battleWindow, battleMaxY, battleMaxX, 5, clear2);
																	printMiddle(battleWindow, battleMaxY, battleMaxX, 4, clear3);
																	printMiddle(battleWindow, battleMaxY, battleMaxX, 3, clear4);
																	printMiddle(battleWindow, battleMaxY, battleMaxX, 2, clear5);
																	wrefresh(battleWindow);
																	printMiddle(battleWindow, battleMaxY, battleMaxX, 4, "You have succesfully hacked the computer!");
																	mainPlayer.cash += (computerElo / 10) - 5;
																	mainPlayer.amountHacked += 1;
		
																}
																else
																{
																	printMiddle(battleWindow, battleMaxY, battleMaxX, 6, clear1);
																	printMiddle(battleWindow, battleMaxY, battleMaxX, 5, clear2);
																	printMiddle(battleWindow, battleMaxY, battleMaxX, 4, clear3);
																	printMiddle(battleWindow, battleMaxY, battleMaxX, 3, clear4);
																	printMiddle(battleWindow, battleMaxY, battleMaxX, 2, clear5);
																	wrefresh(battleWindow);
																	printMiddle(battleWindow, battleMaxY, battleMaxX, 4, "                                          ");
																	printMiddle(battleWindow, battleMaxY, battleMaxX, 4, "You have failed to hack the computer...");
																}
																wrefresh(battleWindow);
																getch();
																break;
															}
															else
															{
																break;
															}
															wrefresh(battleWindow);
														}

													}
													if (danielGameInput == 'x')
													{
														int hackBonus = mainPlayer.amountHacked * 10;
														mainPlayer.cash += hackBonus;
														endwin();
														wclear(danielGameWin);
														danielMainGameLoop = true;
														preLoop = true;
														break;
														refresh();
														curs_set(0);

													}
												
												}
												endwin();
												danielGameLoop = true;
												refresh();

												


											}
											
											
										}
										
										
									}
									
										
								}

								if (inboxMenuInput == "GO BACK")
								{

									inboxLoop = true;
									refresh();
								}


							}
						}
						if (inputSecondScreen == "LEADERBOARD")						//work on
						{
							bool leaderboardLoop = false;
							while (!leaderboardLoop)
							{
								wrefresh(secondScreenWin);
								WINDOW * leaderboard = newwin(20, 70, 1, 1);
								refresh();
								wborder(leaderboard, 0, 0, 0, 0, 0, 0, 0, 0);
								wattron(leaderboard, COLOR_PAIR(1));
								int leaderboardMaxY, leaderboardMaxX;
								getmaxyx(leaderboard, leaderboardMaxY, leaderboardMaxX);
								printMiddle(leaderboard, leaderboardMaxY, leaderboardMaxX, 9, "");
								wattroff(leaderboard, COLOR_PAIR(1));

								keypad(leaderboard, true);
								string leaderboardChoices[1] = { "GO BACK" };
								int leaderboardChoice;
								int leaderboardHighlight = 0;
								while (1)
								{
									for (int n = 0; n < 1; n++)
									{
										if (n == leaderboardHighlight)
											wattron(leaderboard, A_REVERSE);
										mvwprintw(leaderboard, n + 17, 2, leaderboardChoices[n].c_str());
										wattroff(leaderboard, A_REVERSE);
									}
									leaderboardChoice = wgetch(leaderboard);
									switch (leaderboardChoice)
									{
									default:
										break;
									}
									if (leaderboardChoice == 10)
										break;
								}
								string inputLeaderboard = leaderboardChoices[leaderboardHighlight];
								wrefresh(leaderboard);
								if (inputLeaderboard == "GO BACK")
								{
									leaderboardLoop = true;
									refresh();
								}
								wrefresh(leaderboard);
							}
						}
		
						if (inputSecondScreen == "GO BACK TO MAIN MENU")
						{
							/*
							string sqlSelect = "UPDATE danielGameTable SET danielElo = ?, danielCash = ?, danielAmountHacked = ?";
							sqlite3_prepare(db, sqlSelect.c_str(), sqlSelect.size(), &stmt, nullptr);
							sqlite3_bind_int(stmt, 1, mainEloRating);
							sqlite3_bind_int(stmt, 2, mainPlayer.cash);
							sqlite3_bind_int(stmt, 3, mainPlayer.amountHacked);
							sqlite3_step(stmt);
							sqlite3_finalize(stmt);
							sqlite3_close(db);
							*/
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
			sqlite3_close(db);
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
				string instructionString6 = "BECOMING A FIRST CLASS HACKER.                        ";
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
