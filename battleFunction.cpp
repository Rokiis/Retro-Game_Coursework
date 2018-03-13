void battleFunction()
{
	bool battleLoop = false;
	while (!battleLoop)
	{
		WINDOW * battleWindow = newwin(20, 70, 1, 1);
		refresh();
		wborder(battleWindow, 0, 0, 0, 0, 0, 0, 0, 0);
		int battleMaxY, battleMaxX;
		getmaxyx(battleWindow, battleMaxY, battleMaxX);
		printMiddle(battleWindow, battleMaxY, battleMaxX, 9, "TEST");
		wrefresh(battleWindow);
		keypad(battleWindow, true);
		string battleChoices[4] = { "OPTION1", "OPTION2", "OPTION3", "OPTION4" };
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
					mvwprintw(battleWindow, i + 7, 3, battleChoices[i].c_str());
				}
				if (i == 1)
				{
					mvwprintw(battleWindow, i + 6, 15, battleChoices[i].c_str());
				}
				if (i == 2)
				{
					mvwprintw(battleWindow, i + 8, 3, battleChoices[i].c_str());
				}
				if (i == 3)
				{
					mvwprintw(battleWindow, i + 7, 15, battleChoices[i].c_str());
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
		wrefresh(battleWindow);
		if (inputBattle == "OPTION1")
		{
			battleLoop = true;
			refresh();
		}
		wrefresh(battleWindow);
	}
	refresh();
}
