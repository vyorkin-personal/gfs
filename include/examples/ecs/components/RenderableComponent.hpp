#pragma once

#include "examples/Example.hpp"

class RenderableComponent: public Component {
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
