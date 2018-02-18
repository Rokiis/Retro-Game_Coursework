#include <cstdlib>
#include <cstdint>
#include <vector>
#include "Game.h"
#include "ObjectField.h"


void ObjectField::update() {
	// update existing objects
	for (size_t i = 0; i < object_set.size(); i++) {
		if (object_set.at(i).getPos().y > field_bounds.bot())
			object_set.erase(object_set.begin() + i);

		object_set.at(i).update();
	}

	int spam;
	int smap;
	spam = field_bounds.width();
	smap = spam - 2;
	// spawn a new object
	bricks s(rand() % spam + 0, rand() % 7 + 2);
	object_set.push_back(s);
}

void ObjectField::erase(size_t i) {
	object_set.erase(object_set.begin() + i);
}

std::vector<bricks> ObjectField::getData() const { return object_set; }

void ObjectField::setBounds(rect a) { field_bounds = a; }



bricks::bricks(int nx, int ny) { pos.x = nx; pos.y = ny; }
	void bricks::update() { pos.y; }

vec2i bricks::getPos() const { return pos; }