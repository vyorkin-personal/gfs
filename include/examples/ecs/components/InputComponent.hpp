#pragma once

#include "examples/Example.hpp"

class InputComponent: public Component {
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
