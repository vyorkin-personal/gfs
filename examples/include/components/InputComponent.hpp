#pragma once

#include "Example.hpp"

class InputComponent: public ecs::Component {
    public:
	void move() {
	    moving = true;
	}

	void stop() {
	    moving = false;
	}

	bool isMoving() const {
	    return moving;
	}

    private:
	bool moving;
};
