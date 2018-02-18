#ifndef SPACEOBJECT_H
#define SPACEOBJECT_H
#include <vector>
class bricks {

public:
	bricks(int, int);
	void update();

	vec2i getPos() const;
	void setPos(vec2i);

private:
	vec2i pos;
};



class ObjectField {

public:
	void update();
	void erase(size_t);
	std::vector<bricks> getData() const;

	void setBounds(rect);

private:
	rect field_bounds;
	std::vector<bricks> object_set;

};

#endif