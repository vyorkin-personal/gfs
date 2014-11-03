#pragma once

#include "Component.hpp"

class RenderableComponent: public gfs::Component {
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
