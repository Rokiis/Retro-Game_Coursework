#include <cstdlib>
#include <cstdint>
#include <vector>
#include "Game.h"
#include "BallMovement.h"
void BallMovement::update() {
	// update existing objects
		ball.update();
}

std::vector<ball> BallMovement::getData() const { return object_set; }

void BallMovement::setBounds(rect a) { field_bounds = a; }



ball::ball(int nx, int ny) { pos.x = nx; pos.y = ny; }
void ball::update() { pos.y; }

vec2i ball::getPos() const { return pos; }



/*class ball {
public:
	int x, y;
	int speedX, speedY;
	ball() {
		x = ball.pos.x
			y = ball.pos.y
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

};*/

