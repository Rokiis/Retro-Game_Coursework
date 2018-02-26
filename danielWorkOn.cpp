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
	int winTrack1, winTrack2;
	winTrack1 = winTrack2 = 0;

	for (int i = 0; i < 10; i++)
	{
		
		winLoss = rand() % 1;
		eloExp1 = eloExpected(player1, player2);
		eloExp2 = eloExpected(player2, player1);
		player1 = elo(player1, eloExp1, winLoss, kFactor);
		player2 = elo(player2, eloExp2, !winLoss, kFactor);
		if (winLoss == 1)
		{
			cout << winLoss << endl;
			cout << "Win for player1" << endl;
			cout << "Player1: " << player1 << endl;
			cout << "Player2: " << player2 << endl;
			cout << endl;
			winTrack1 += 1;
		}
		else
		{
			cout << winLoss << endl;
			cout << "Win for player2" << endl;
			cout << "Player1: " << player1 << endl;
			cout << "Player2: " << player2 << endl;
			cout << endl;
			winTrack2 += 1;
		}
	}
	cout << "final results" << endl;
	cout << "Player1 elo: " << player1 << endl;
	cout << "Player1 wins: " << winTrack1 << endl;
	cout << "Player2 elo: " << player2 << endl;
	cout << "Player2 wins: " << winTrack2 << endl;

	system("pause");
	return 0;
}
