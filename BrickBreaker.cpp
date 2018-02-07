//brick destroyer game
//Rnavick
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <thread>
#include <cmath>
#include <time.h>
using namespace std;
int onPlay = 1;
const int W = 50;           //game field size
const int H = 20;
int score;
int board[100][100];



void gotoXY(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void resetboard() {
	for (int j = 0; j<H; j++) {
		for (int i = 0; i<W; i++) {
			board[i][j] = 0;
		}
	}
}
void drawPoint(int x, int y, int value) {
	board[x][y] = value;
}
void erasePoint(int x, int y) {
	board[x][y] = 0;
}
void drawBorder() {
	for (int i = 0; i<W; i++) { drawPoint(i, 0, 1); }
	for (int i = 0; i<W; i++) { drawPoint(i, H - 1, 1); }
	for (int j = 0; j<H; j++) { drawPoint(0, j, 1); }
	for (int j = 0; j<H; j++) { drawPoint(W - 1, j, 1); }
}





//BALL CLASS
class ball {
public:
	int x, y;
	int speedX, speedY;
	ball() {
		x = 5;
		y = 5;
		speedX = 1;
		speedY = -1;
	}
	void draw() {
		drawPoint(x, y, 3);
	}
	void move() {
		if (board[x][y] == 3) {
			erasePoint(this->x, this->y);
		}
		this->x = this->x + speedX;
		this->y = this->y + speedY;
		if (board[x][y] == 0) {
			drawPoint(x, y, 3);
		}
	}
	void checkbounce() {
		if (x >= W - 1) { speedX = -1 * speedX; }
		if (x <= 0) { speedX = -1 * speedX; }
		if (y <= 0) { speedY = -1 * speedY; }
		if (y >= H - 1) { speedY = -1 * speedY; }

		if (board[x][y] == 4) { speedY = -1 * speedY; }
	}
	void checkcollision() {
		if (board[this->x][this->y] == 2) {
			erasePoint(this->x, this->y);
			////////////////////////////
			if (board[x - 1][y] == 0) { speedX = -1; }
			if (board[x + 1][y] == 0) { speedX = 1; }
			if (board[x][y + 1] == 0) { speedY = 1; }
			if (board[x][y - 1] == 0) { speedY = -1; }
			////////////////////////////
			if (board[x - 1][y + 1] == 0) { speedY = -1 * speedY; speedX = -1 * speedX; }
			if (board[x + 1][y + 1] == 0) { speedY = -1 * speedY; speedX = -1 * speedX; }
			if (board[x + 1][y - 1] == 0) { speedY = -1 * speedY; speedX = -1 * speedX; }
			if (board[x - 1][y - 1] == 0) { speedY = -1 * speedY; speedX = -1 * speedX; }

			score += 10;
		}

	}
	void checkbound(int &onplay, int &lose) {
		if (this->y >= H - 1) {
			onplay = 0;
			lose = 1;
		}
	}

};



//BRICKS
class bricks {
public:
	void init(int startX, int startY) {
		for (int j = 0; j < H; j++) {
			for (int i = 0; i < W; i++) {
				if (i >= startX & i < W - startX & j >= startY & j < startY + 4) { board[i][j] = 2; }
			}
		}
	}
	void vanish(int x, int y) {
		board[x][y] = 0;
	}
	int x, y, stat;
	void draw() {
		drawPoint(x, y, 2);
	}
};


// Cursor/Player/Pad/Plate, whatever :D 
class pad {
public:
	int x;  //Position of the pad
	int length;
	void init() {
		this->x = 12;
		this->length = 106;
		for (int i = this->x; i<this->x + this->length; i++) { drawPoint(i, H - 2, 4); }
	}
	void moveL() {
		x--;
		if (x<1) { x = 1; }
		for (int i = 1; i<x; i++) { drawPoint(i, H - 2, 0); }
		for (int i = x; i<x + length; i++) { drawPoint(i, H - 2, 4); }
		for (int i = x + length; i<W - 1; i++) { drawPoint(i, H - 2, 0); }
	}
	void moveR() {
		x++;
		if (x>W - 2) { x = W - 2; }
		for (int i = 1; i<x; i++) { drawPoint(i, H - 2, 0); }
		for (int i = x; i<x + length; i++) { drawPoint(i, H - 2, 4); }
		for (int i = x + length; i<W - 1; i++) { drawPoint(i, H - 2, 0); }
	}
}myPad;



void listenInput() {
	int k[9] = { 13,32,36,37,38, 39, 40,41,42 };
	int i = 0;
	while (1)
	{
		for (int n = 0; n<9; n++)
		{
			i = k[n];
			if (GetAsyncKeyState(i) == -32767)
			{ 
				if (i == 32)
				{
					onPlay = 0;
				}
				if (i == 37)
				{
					myPad.moveL();
				}
				else if (i == 39)
				{
					myPad.moveR();
				}
			}
		}
	}
}
////////////////////

bricks myBrks;
ball myBall;
void startGame() {
	int lose = 0;
	system("cls");
	score = 0;
	onPlay = 1;
	resetboard();
	drawBorder();

	myPad.init();
	myBall = ball();
	myBall.draw();
	myBrks.init(7, 4);
	while (onPlay) {
		myBall.move();
		myBall.checkbounce();
		myBall.checkcollision();
		myBall.checkbound(onPlay, lose);
	}

	for (int j = 0; j < H; j++) {
		for (int i = 0; i < W; i++) {
			gotoXY(i, j);
			if (board[i][j] == 1) { cout << "0"; }
			else if (board[i][j] == 2) { cout << "0"; }
			else if (board[i][j] == 3) { cout << "0"; }
			else if (board[i][j] == 4) { cout << "0"; }
			else { cout << " "; }
		}
	}

	gotoXY(45, 4);
	cout << "SCORE:" << score;
	if (lose == 1) {
		system("cls");
		drawBorder();
		gotoXY(10, 6); cout << "GAME OVER!";
		gotoXY(10, 7); cout << "SCORE:" << score;
		Sleep(3000);
	}
}


int main() {
	startGame();
	Sleep(1000);
	return 0;
}
