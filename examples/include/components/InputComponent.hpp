#pragma once

#include "Component.hpp"

class InputComponent: public gfs::Component {
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
