#pragma once

#include "Example.hpp"

class RenderableComponent: public ecs::Component {
    public:
	void draw() {
	    drawn = true;
	}

	bool isDrawn() const {
	    return drawn;
	}
    private:
	bool drawn;
};
