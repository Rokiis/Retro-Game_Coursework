if (inputSecondScreen == "LEADERBOARD")
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
								string leaderboardChoices[1] = {"GO BACK" };
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
