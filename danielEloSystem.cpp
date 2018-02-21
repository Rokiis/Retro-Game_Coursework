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

	Player Daniel, Simon;
	Daniel.name = "Daniel";
	Simon.name = "Simon";
	Daniel.eloRating = 2000;
	Simon.eloRating = 1800;

	float eloExp1, eloExp2;
	eloExp1 = eloExpected(Daniel.eloRating, Simon.eloRating);
	eloExp2 = eloExpected(Simon.eloRating, Daniel.eloRating);
	int newElo1 = elo(Daniel.eloRating, eloExp1, winLoss, 20);
	int newElo2 = elo(Simon.eloRating, eloExp2, !winLoss, 20);
	cout << "Daniel elo rating = " << Daniel.eloRating << endl;
	cout << "Simon elo rating = " << Simon.eloRating << endl;
	cout << "Exepected score 1: " << eloExp1 << " Expected score 2: " << eloExp2 << endl;
	if (winLoss == 1)
	{
	cout << Daniel.name << " won so new elo rating = " << newElo1 << endl;
	cout << Simon.name << " lost so new elo rating = " << newElo2 << endl;
	}
	else
	{
		cout << Daniel.name << " lost so new elo rating = " << newElo1 << endl;
		cout << Simon.name << " won so new elo rating = " << newElo2 << endl;
	}
	
	system("pause");
	return 0;
}

//snake with code
