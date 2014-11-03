#pragma once

#include "Component.hpp"

class VelocityComponent: public gfs::Component {
    public:
	VelocityComponent(const float x, const float y) {
	    this->x = x;
	    this->y = y;
	}

	float getX() const {
	    return x;
	}

	float getY() const {
	    return y;
	}
    private:
	float x;
	float y;
};
