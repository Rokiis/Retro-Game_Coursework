//d.jones
//group d2
#include "curses.h" // or #include <ncurses.h> (linux) sudo apt-get install libncurses5-dev libncursesw5-dev
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <time.h>
#include <vector>
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
	srand(time(NULL)); //windows only - random gen per session

	while (!mainMenuLoop)
	{
		int email1Money, email2Money, email3Money;
		email1Money = 100;
		email2Money = email1Money * 2;
		email3Money = email2Money * 2;
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
		int mainMaxY, mainMaxX;
		getmaxyx(mainMenu, mainMaxY, mainMaxX);

		init_pair(1, COLOR_GREEN, 0);
		init_pair(69, COLOR_RED, 0);	//colour initialisations
		init_pair(2, COLOR_CYAN, 0);
		init_pair(3, COLOR_MAGENTA, 0);
		init_pair(4, COLOR_WHITE, 0);
		init_pair(5, COLOR_YELLOW, 0);
		init_color(COLOR_WHITE, 255, 105, 180);



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
			case KEY_UP:
				mainMenuHighlight--;
				if (mainMenuHighlight == -1)
					mainMenuHighlight = 2;
				break;
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
					case KEY_UP:
						characterCreationHighlight--;
						if (characterCreationHighlight == -1)
							characterCreationHighlight = 1;
						break;
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
					string playerSessionName;
					wrefresh(inboxMenu);
					mvwscanw(inboxMenu, 14, 2, "%s", playerSessionName.c_str());
					wrefresh(inboxMenu);
					noecho();
					curs_set(0);
					mvwprintw(inboxMenu, 14, 2, "WELCOME, %s. Press any key to continue...", playerSessionName.c_str());

					int playerSessionCash = 0;
					string playerSessionStrikes = " ";				//important values

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
						mvwprintw(secondScreenWin, 1, 2, "NAME: %s", playerSessionName.c_str());
						wattroff(secondScreenWin, COLOR_PAIR(4));
						wattron(secondScreenWin, COLOR_PAIR(5));
						mvwprintw(secondScreenWin, 1, 55, "CASH: %d", playerSessionCash);
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
							case KEY_UP:
								secondScreenHighlight--;
								if (secondScreenHighlight == -1)
									secondScreenHighlight = 4;
								break;
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
								vector<string> possibleSender = { "Daniel", "Nick", "Hazar", "Rokkas", "Patryk", "Laur", "Dr Billings", "Dr Grawemeyer",
																  "Hannah", "Bob", "Jim", "Simeon", "Marianne", "Fritzli", "Phyllis", "Ursulla",
																  "Mike", "René", "Tyquoterius", "Andris", "Chez", "Svaraaj", "Saeed", "Yasser" };
								vector<string> possibleSubject = { "Hacking my GF's Facebook account", "Breaking into the pentagon", "Making my grades at school higher",
																   "Leaking the contents of a database", "Hacking into and changing the balance of my bank account", "SQL Injection on vulnernable website",
																   "Denial of Service attack on my school network" };
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
													mvwprintw(inboxMenu, (5 * m + 3) + 3, 3, "Reward: %d", email1Money);
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
									case KEY_UP:
										inboxHighlight--;
										if (inboxHighlight == -1)
											inboxHighlight = 3;
										break;
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
								if (inboxMenuInput == "EMAIL 2")
								{
									inboxLoop = true;
									refresh();
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
				printMiddle(howToPlay, instructionMaxY, instructionMaxX, 9, "INSTRUCTIONS");
				int howToMaxY, howToMaxX;
				getmaxyx(howToPlay, howToMaxY, howToMaxX);
				string test = "WELCOME TO STUXNET";
				string test1 = "TO BEGIN THE GAME, SELECT THE 'PLAY' OPTION -";
				string test2 = "AND ENTER YOUR DESIRED ALIAS.";												//work on
				string test3 = "THE GAME WILL PRESENT YOU WITH A SERIES OF CHALLENGES";
				string test4 = "COMPLETE THEM AND YOU WILL PROGRESS ON YOUR PATH TO BECOMING A HACKER";
				/*int x = test.length();
				mvwprintw(howToPlay, howToMaxY/2, (howToMaxX-x)/2, test.c_str());*/   // <- alternative way if my function fails
				/*printMiddle(howToPlay, howToMaxY, howToMaxX, 5, test);
				printMiddle(howToPlay, howToMaxY, howToMaxX, 4, test1);
				printMiddle(howToPlay, howToMaxY, howToMaxX, 3, test2);
				printMiddle(howToPlay, howToMaxY, howToMaxX, 2, test3);
				printMiddle(howToPlay, howToMaxY, howToMaxX, 1, test4);*/


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
						mvwprintw(howToPlay, m + 7, 2, howToPlayChoices[m].c_str());
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
