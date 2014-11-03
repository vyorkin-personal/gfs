#pragma once

#include "Component.hpp"

class PositionComponent: public gfs::Component {
    public:
	PositionComponent(const float x, const float y) {
	    this->x = x;
	    this->y = y;
	}

	float getX() const {
	    return x;
	}

	float getY() const {
	    return y;
	}

	void move(const float dx, const float dy) {
	    x += dx;
	    y += dy;
	}

    private:
	float x;
	float y;
};
