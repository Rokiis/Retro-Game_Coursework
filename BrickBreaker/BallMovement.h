#ifndef BALLMOVEMENT_H
#define BALLMOVEMENT_H
#include <vector>
class ball {

public:
	ball(int, int);
	void update();

	vec2i getPos() const;
	void setPos(vec2i);

private:
	vec2i pos;
};



class BallMovement {

public:
	void update();
	std::vector<ball> getData() const;

	void setBounds(rect);

private:
	rect field_bounds;
	std::vector<ball> object_set;

};

#endif