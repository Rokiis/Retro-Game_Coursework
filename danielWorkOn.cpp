
	int kFactor = 20;				
	float player1, player2;
	player1 = 1700;
	player2 = 1400;
	float eloExp1, eloExp2, eloGap1, eloGap2;
	int winLoss = rand() % 2;

	for(int i = 0; i < 30; i++)
	{
		winLoss = rand() % 2;
		eloExp1 = eloExpected(player1, player2); 
		eloExp2 = eloExpected(player2, player1);
		player1 = elo(player1, eloExp1, winLoss, kFactor);
		player2 = elo(player2, eloExp2, !winLoss, kFactor);
		if (winLoss == 1)
		{
			cout << "Win for player1" << endl;
			cout << "Player1: " << player1 << endl;
			cout << "Player2: " << player2 << endl;
			cout << endl;
		}
		else
		{
			cout << "Win for player2" << endl;
			cout << "Player1: " << player1 << endl;
			cout << "Player2: " << player2 << endl;
			cout << endl;
		}
	}
	cout << "final results" << endl;
	cout << "Player1 elo: " << player1 << endl;
	cout << "Player2 elo: " << player2 << endl;
