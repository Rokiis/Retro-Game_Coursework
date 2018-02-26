#include <iostream>
#include <string>
#include <math.h>
#include <ctime>
using namespace std;

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

int main()
{

	srand(time(NULL));
	int kFactor = 20;
	int player1, player2;
	player1 = 1450;
	player2 = 1400;
	float eloExp1, eloExp2, eloGap1, eloGap2;
	int winLoss = rand() % 2;

	for (int i = 0; i < 10; i++)
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

	system("pause");
	return 0;
}
