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
class Player
{
public:
	string name;
	float eloRating;
};


int main()
{
	
	
	srand(time(NULL));
	int K = 20;
	int winLoss = rand() % 2;
	cout << winLoss << endl;

	Player Player1, Player2;
	Player1.name = "Daniel";
	Player2.name = "Hugh";
	Player1.eloRating = 1600;
	Player2.eloRating = 1400;

	int k = 20;
	float eloExp1, eloExp2;
	eloExp1 = eloExpected(Player1.eloRating, Player2.eloRating);
	eloExp2 = eloExpected(Player2.eloRating, Player1.eloRating);
	int newElo1 = elo(Player1.eloRating, eloExp1, winLoss, k);
	int newElo2 = elo(Player2.eloRating, eloExp2, !winLoss, k);

	cout << Player1.name <<" elo rating = " << Player1.eloRating << endl;
	cout << Player2.name <<" elo rating = " << Player2.eloRating << endl;
	cout << "Exepected score 1: " << eloExp1 << " Expected score 2: " << eloExp2 << endl;

	if (winLoss == 1)
	{
		cout << Player1.name << " won " << newElo1 - Player1.eloRating << " points" << endl;
		cout << Player2.name << " lost " << Player2.eloRating - newElo2 << " points" << endl;
		cout << Player1.name << " won, so new elo rating = " << newElo1 << endl;
		cout << Player2.name << " lost, so new elo rating = " << newElo2 << endl;

	}
	else
	{
		cout << Player1.name << " lost " << Player1.eloRating - newElo1 << " points" << endl;
		cout << Player2.name << " won " << newElo2 - Player2.eloRating << " points" << endl;
		cout << Player1.name << " lost, so new elo rating = " << newElo1 << endl;
		cout << Player2.name << " won, so new elo rating = " << newElo2 << endl;

	}
	
	system("pause");
	return 0;
}

